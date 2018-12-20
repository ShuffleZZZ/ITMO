package ru.itmo.wm4.service;

import org.springframework.stereotype.Service;
import ru.itmo.wm4.domain.Notice;
import ru.itmo.wm4.domain.User;
import ru.itmo.wm4.form.NoticeCredentials;
import ru.itmo.wm4.repository.NoticeRepository;

import java.util.List;

@Service
public class NoticeService {
    private final NoticeRepository noticeRepository;

    private final TagService tagService;

    public NoticeService(NoticeRepository noticeRepository, TagService tagService) {
        this.noticeRepository = noticeRepository;
        this.tagService = tagService;
    }

    public List<Notice> findByOrderByCreationTimeDesc() {
        return noticeRepository.findByOrderByCreationTimeDesc();
    }

    public Notice findById(Long noticeId) {
        return noticeId == null ? null : noticeRepository.findById(noticeId).orElse(null);
    }

    public void save(NoticeCredentials noticeCredentials, User user) {
        Notice notice = new Notice();
        notice.setText(noticeCredentials.getText());
        String[] Tags = noticeCredentials.getTags().trim().split("\\s+");
        for (String tag: Tags) {
            notice.getTags().add(tagService.get(tag));
        }
        user.addNotice(notice);
        noticeRepository.save(notice);
    }
}
