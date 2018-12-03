package ru.itmo.webmail.model.service;

import ru.itmo.webmail.model.domain.Talk;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.model.repository.TalkRepository;
import ru.itmo.webmail.model.repository.impl.TalkRepositoryImpl;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class TalkService {
    private UserService userService = new UserService();
    private TalkRepository talkRepository = new TalkRepositoryImpl();

    public void validateSending(String login, String text) throws ValidationException {
        if (userService.findByLoginOrEmail(login) == null) {
            throw new ValidationException("This user doesn't exist");
        }

        if (text == null || text.isEmpty()) {
            throw new ValidationException("Put in the message");
        }
    }

    public void send(Long source, Long target, String text) {
        talkRepository.save(new Talk(source, target, text));
    }

    private List<Talk> findAllForUser(Long id) {
        return talkRepository.findAllForUser(id);
    }

    public List<Chat> findAllFrontForUser(Long id) {
        List<Talk> talks = findAllForUser(id);
        List<Chat> result = new ArrayList<>();
        for (Talk talk: talks) {
            result.add(new Chat(userService.findById(talk.getSourceUserId()).getLogin(),
                    userService.findById(talk.getTargetUserId()).getLogin(), talk.getText(),
                    talk.getCreationTime()));
        }
        return result;
    }

    public static class Chat {
        private String source;
        private String target;
        private String text;
        private Date time;

        public Date getTime() {
            return time;
        }

        public void setTime(Date time) {
            this.time = time;
        }

        public Chat(String source, String target, String text, Date time) {
            this.target = target;
            this.source = source;
            this.text = text;
            this.time = time;
        }


        public String getText() {
            return text;
        }

        public void setText(String text) {
            this.text = text;
        }

        public String getSource() {
            return source;
        }

        public void setSource(String source) {
            this.source = source;
        }

        public String getTarget() {
            return target;
        }

        public void setTarget(String target) {
            this.target = target;
        }
    }
}