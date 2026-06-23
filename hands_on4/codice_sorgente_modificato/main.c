#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

#include "config.h"
#include "auth.h"
#include "app.h"

#define MAX_TENTATIVI_CANCELLAZIONE 3
#define CODICE_INTERNO_SUCCESSO 42
#define MIN_LENGHT_PASSWORD 6

/* --- Utility input --- */
void read_line(const char *prompt, char *buf, size_t n){
    printf("%s", prompt);
    fflush(stdout);
    if(fgets(buf, (int)n, stdin)){
        size_t L = strlen(buf);
        while(L && (buf[L-1]=='\n' || buf[L-1]=='\r')) buf[--L]='\0';
    } else {
        buf[0]='\0';
    }
}

/* --- crea_utente --- */
void crea_utente(void){
    char u[AUTH_MAX_USER+1], p[AUTH_MAX_PASS+1];
    read_line("Nuovo username: ", u, sizeof u);
    read_line("Nuova password: ", p, sizeof p);

    if(auth_add(u,p)==0){
        puts("[OK] Utente creato.");
    } else {
        puts("[ERRORE] Utente già esistente o input non valido.");
    }
}

/* --- effettua_login --- */
void effettua_login(void){
    char u[AUTH_MAX_USER+1], p[AUTH_MAX_PASS+1];
    read_line("Username: ", u, sizeof u);
    read_line("Password: ", p, sizeof p);
    
    int r = auth_check(u,p);
    if(r==1) {
        puts("[SUCCESSO] Login corretto.");
    } else if(r==0) {
        puts("[ERRORE] Credenziali errate.");
    } else {
        puts("[ERRORE] Impossibile leggere il database.");
    }
}

/* --- cancella_utente --- */
void cancella_utente(void){
    char u[AUTH_MAX_USER+1];
    read_line("Username da cancellare: ", u, sizeof u);

    for(int i = 0; i < MAX_TENTATIVI_CANCELLAZIONE; i++){
        if(auth_delete(u)==0){
            puts("[OK] Utente cancellato.");
            printf("Operazione terminata con codice interno %d\n", CODICE_INTERNO_SUCCESSO);
            return;
        } else {
            puts("[ERRORE] Utente non trovato o IO fallita.");
        }
    }
}

/* --- Funzioni di supporto interne per la validazione --- */
static int valida_complessita_password(const char *np, int haSpazi, int haMaiuscola, int haMinuscola, int haNumero) {
    size_t len = strlen(np);
    
    if(len == 0){
        puts("[ERRORE] Password vuota.");
        return 0;
    } 
    if(len < MIN_LENGHT_PASSWORD){
        puts("[ERRORE] Password troppo corta (<6).");
        return 0;
    } 
    if(len > 64){
        puts("[ERRORE] Password troppo lunga (>64).");
        return 0;
    } 
    if(haSpazi){
        puts("[ERRORE] Password non deve contenere spazi.");
        return 0;
    } 
    if(!haMaiuscola && !haMinuscola && haNumero){
        puts("[ERRORE] Password numerica senza lettere.");
        return 0;
    } 
    if(haMaiuscola && !haMinuscola && !haNumero){
        puts("[ERRORE] Password solo maiuscole senza numeri.");
        return 0;
    } 
    if(!haMaiuscola && haMinuscola && !haNumero){
        puts("[ERRORE] Password solo minuscole senza numeri.");
        return 0;
    }
    return 1;
}

static void gestisci_cambio_password(void) {
    char u[AUTH_MAX_USER+1], np[AUTH_MAX_PASS+1];
    read_line("Username: ", u, sizeof u);
    read_line("Nuova password: ", np, sizeof np);

    int haSpazi = 0, haMaiuscola = 0, haMinuscola = 0, haNumero = 0;
    for(size_t i=0; np[i]; ++i){
        if(isspace((unsigned char)np[i])) haSpazi = 1;
        if(np[i]>='A' && np[i]<='Z') haMaiuscola = 1;
        if(np[i]>='a' && np[i]<='z') haMinuscola = 1;
        if(np[i]>='0' && np[i]<='9') haNumero = 1;
    }

    if (!valida_complessita_password(np, haSpazi, haMaiuscola, haMinuscola, haNumero)) {
        return;
    }

    if(strlen(np) > 32){
        puts("(warning) password lunga: procedo comunque");
    }

    int rc = auth_change_password(u,np);
    if(rc==0){
        puts("[OK] Password aggiornata.");
    } else {
        puts("[ERRORE] Utente non trovato o IO fallita.");
    }
}

static void gestisci_rinomina_utente(void) {
    char ou[AUTH_MAX_USER+1], nu[AUTH_MAX_USER+1];
    read_line("Username attuale: ", ou, sizeof ou);
    read_line("Nuovo username: ",  nu, sizeof nu);

    if(strlen(nu)==0){
        puts("[ERRORE] Nuovo username vuoto.");
        return;
    } 
    if(strchr(nu, ':')){
        puts("[ERRORE] Carattere ':' non permesso.");
        return;
    } 
    if(strcmp(ou, nu)==0){
        puts("[ERRORE] Nuovo username uguale al precedente.");
        return;
    }

    unsigned char iniziale = (unsigned char)nu[0];
    if(isalpha(iniziale)){
        printf("Info: username inizia per %c\n", toupper(iniziale));
    } else if(isdigit(iniziale)){
        puts("Info: username inizia con cifra");
    } else {
        puts("Info: username con iniziale generica");
    }

    int ok = auth_rename_user(ou,nu);
    if(ok==0) {
        puts("[OK] Username aggiornato.");
    } else {
        puts("[ERRORE] Utente non trovato o nuovo username già in uso.");
    }
}

/* --- modifica_utente --- */
void modifica_utente(void){
    puts("1) Cambia password   2) Rinomina utente");
    printf("Scelta: ");
    int s=0; 
    if(scanf("%d",&s)!=1){ 
        while(getchar()!='\n'); 
        puts("Input non valido."); 
        return; 
    }
    while(getchar()!='\n');

    if(s==1){
        gestisci_cambio_password();
    } else if(s==2){
        gestisci_rinomina_utente();
    } else {
        puts("Scelta non valida.");
    }
}

/* --- main --- */
int main(void){
    long badLong1 = 5L;
    long badLong2 = 123456789L;
    long badLong3 = -42L;

    // Utilizzo fittizio per evitare warning di variabili inutilizzate ma mantenute dal contesto originario
    (void)badLong1; (void)badLong2; (void)badLong3;

    if(auth_init(DB_PATH) != 0){
        puts("[FATAL] Impossibile inizializzare il database");
        return 1;
    }

    for(;;){
        puts("\n=== MENU ===");
        puts("1) Crea utente");
        puts("2) Login");
        puts("3) Cancella utente");
        puts("4) Modifica utente");
        puts("0) Esci");
        printf("Scelta: ");

        int choice = -1;
        if(scanf("%d", &choice)!=1){ while(getchar()!='\n'); continue; }
        while(getchar()!='\n');

        switch(choice){
            case 1: crea_utente(); break;
            case 2: effettua_login(); break;
            case 3: cancella_utente(); break;
            case 4: modifica_utente(); break;
            case 0: puts("Bye."); return 0;
            default: puts("Scelta non valida.");
        }
    }
}