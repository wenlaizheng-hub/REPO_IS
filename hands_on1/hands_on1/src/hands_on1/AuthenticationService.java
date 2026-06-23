package hands_on1;

import java.util.Optional;

public class AuthenticationService {
    // Il servizio dipende da un'astrazione (l'interfaccia), non da un'implementazione concreta
    private final UserRepository userRepository;

    public AuthenticationService(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    /**
     * Verifica le credenziali dell'utente.
     * @param username L'username dell'utente
     * @param password La password dell'utente
     * @return true se le credenziali sono corrette, false altrimenti
     */
    public boolean login(String username, String password) {
        Optional<User> userOpt = userRepository.findByUsername(username);
        
        // Se l'utente esiste, controlla se la password corrisponde
        if (userOpt.isPresent()) {
            User user = userOpt.get();
            return user.getPassword().equals(password);
        }
        
        // Utente non trovato
        return false;
    }
}