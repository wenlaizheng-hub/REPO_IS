package hands_on1;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class AuthenticationServiceTest {

    private UserRepository userRepository;
    private AuthenticationService authService;

    @BeforeEach
    void setUp() {
        // Inizializziamo il repository "finto" in memoria
        userRepository = new InMemoryUserRepository();
        
        // Passiamo il repository al servizio di autenticazione
        authService = new AuthenticationService(userRepository);

        // AGGIORNAMENTO: Ora dobbiamo specificare anche il Role (Role.USER) 
        // quando creiamo l'utente per il test!
        userRepository.save(new User("mario.rossi@azienda.it", "PasswordSicura123", Role.USER));
    }

    @Test
    void testLoginSuccess() {
        boolean result = authService.login("mario.rossi@azienda.it", "PasswordSicura123");
        assertTrue(result, "Il login dovrebbe avere successo con credenziali corrette.");
    }

    @Test
    void testLoginFailureWrongPassword() {
        boolean result = authService.login("mario.rossi@azienda.it", "PasswordSbagliata");
        assertFalse(result, "Il login dovrebbe fallire con una password errata.");
    }

    @Test
    void testLoginFailureUserNotFound() {
        boolean result = authService.login("utente.inesistente@azienda.it", "PasswordSicura123");
        assertFalse(result, "Il login dovrebbe fallire se l'utente non esiste.");
    }
}