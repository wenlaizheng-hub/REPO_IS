package hands_on1;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class InMemoryUserRepository implements UserRepository {
    // Usiamo una mappa per simulare una tabella: la chiave è l'username
    private final Map<String, User> databaseMock = new HashMap<>();

    @Override
    public Optional<User> findByUsername(String username) {
        return Optional.ofNullable(databaseMock.get(username));
    }

    @Override
    public void save(User user) {
        databaseMock.put(user.getUsername(), user);
    }
}