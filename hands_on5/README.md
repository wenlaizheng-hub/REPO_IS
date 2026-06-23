# Aggiornamento Componente AuthController

Sono state applicate modifiche alla classe originale AuthController.java per supportare la gestione degli accessi tramite endpoint dedicati.

## Modifiche Apportate

* **Nuovo Endpoint REST:** Aggiunto l'endpoint REST mappato su @PostMapping("/login").
* **Gestione Richieste:** Il servizio accetta richieste in formato JSON tramite la classe CreateUserRequest.
* **Logica di Autenticazione:** Effettua la verifica delle credenziali confrontandole con i dati presenti all'interno della mappa 'users'.
* **Formato di Risposta:** Ritorna una stringa di testo pari a "OK" in caso di successo o "NOT OK" in caso di fallimento.
