package hands_on1;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class AdminServiceTest {

    private UserRepository userRepository;
    private AdminService adminService;
    private User adminUser;
    private User standardUser;

    @BeforeEach
    void setUp() {
        // Inizializziamo il DB in memoria e il servizio
        userRepository = new InMemoryUserRepository();
        adminService = new AdminService(userRepository);

        // Creiamo un Admin e un Utente Standard per i test
        adminUser = new User("admin@azienda.it", "AdminPass123", Role.ADMIN);
        standardUser = new User("dipendente@azienda.it", "UserPass123", Role.USER);

        // Salviamo l'admin e l'utente standard nel repository
        userRepository.save(adminUser);
        userRepository.save(standardUser);
    }

    @Test
    void testAdminCanAddNewUser() {
        // L'admin tenta di aggiungere un nuovo collega
        assertDoesNotThrow(() -> {
            adminService.addUser(adminUser, "nuovo.collega@azienda.it", "NuovaPass123");
        });

        // Verifichiamo che l'utente sia stato effettivamente salvato
        assertTrue(userRepository.findByUsername("nuovo.collega@azienda.it").isPresent(), 
                   "Il nuovo utente dovrebbe essere presente nel repository.");
    }

    @Test
    void testAddUserFailsIfUsernameAlreadyExists() {
        // L'admin tenta di aggiungere un utente con una mail già esistente (quella del dipendente)
        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
            adminService.addUser(adminUser, "dipendente@azienda.it", "PassDiversa");
        });

        // Verifichiamo che il messaggio d'errore sia corretto
        assertTrue(exception.getMessage().contains("già registrato"));
    }

    @Test
    void testStandardUserCannotAddNewUser() {
        // Un utente standard tenta di aggiungere un altro utente
        Exception exception = assertThrows(SecurityException.class, () -> {
            adminService.addUser(standardUser, "hacker@azienda.it", "HackerPass");
        });

        // Verifichiamo che l'operazione sia stata bloccata per mancanza di permessi
        assertTrue(exception.getMessage().contains("Errore: Operazione consentita solo agli Amministratori."));
        
        // Verifichiamo che l'hacker non sia stato aggiunto al sistema
        assertFalse(userRepository.findByUsername("hacker@azienda.it").isPresent());
    }
}