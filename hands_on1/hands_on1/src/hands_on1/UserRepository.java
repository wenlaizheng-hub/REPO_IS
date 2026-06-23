package hands_on1;

import java.util.Optional;

public interface UserRepository {
    // Cerca un utente tramite il suo username
    Optional<User> findByUsername(String username);
    
    // Salva un nuovo utente (utile per i test e per il futuro PBI 3)
    void save(User user);
}