package ru.itmo.wm4.form.validator;

import org.springframework.stereotype.Component;
import org.springframework.validation.Errors;
import org.springframework.validation.Validator;
import ru.itmo.wm4.form.NoticeCredentials;
import ru.itmo.wm4.service.NoticeService;

@Component
public class NoticeCredentialsAddValidator implements Validator {
    private NoticeService noticeService;

    public NoticeCredentialsAddValidator(NoticeService noticeService) {
        this.noticeService = noticeService;
    }

    @Override
    public boolean supports(Class<?> clazz) {
        return NoticeCredentials.class.equals(clazz);
    }

    @Override
    public void validate(Object target, Errors errors) {
    }
}