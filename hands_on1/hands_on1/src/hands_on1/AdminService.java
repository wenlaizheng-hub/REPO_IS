package hands_on1;

import java.util.Optional;

public class AdminService {
    private final UserRepository userRepository;

    public AdminService(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    /**
     * Permette a un admin di registrare un nuovo utente.
     * * @param requestingUser L'utente che sta eseguendo l'operazione (deve essere ADMIN)
     * @param newUsername L'email del nuovo utente
     * @param newPassword La password del nuovo utente
     * @throws SecurityException se chi richiede l'operazione non è un admin
     * @throws IllegalArgumentException se l'username è già in uso
     */
    public void addUser(User requestingUser, String newUsername, String newPassword) {
        // 1. Controllo dei permessi (Solo gli Admin possono aggiungere utenti)
        if (requestingUser.getRole() != Role.ADMIN) {
            throw new SecurityException("Errore: Operazione consentita solo agli Amministratori.");
        }

        // 2. Controllo dei conflitti (L'email/username deve essere univoca)
        Optional<User> existingUser = userRepository.findByUsername(newUsername);
        if (existingUser.isPresent()) {
            throw new IllegalArgumentException("Errore: L'username '" + newUsername + "' è già registrato nel sistema.");
        }

        // 3. Creazione e salvataggio del nuovo utente
        User newUser = new User(newUsername, newPassword, Role.USER);
        userRepository.save(newUser);
    }
}