package ru.itmo.webmail.model.repository.impl;

import ru.itmo.webmail.model.database.DatabaseUtils;
import ru.itmo.webmail.model.domain.Event;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.repository.EventRepository;

public class EventRepositoryImpl implements EventRepository {
    @Override
    public void newEvent(Event.EventEnum type, User user) {
        DatabaseUtils.executeRequest("INSERT INTO Event (userId, type, creationTime) VALUES (?, ?, NOW())",
                "Unable to logout User.", Long.toString(user.getId()), type.toString());
    }
}
