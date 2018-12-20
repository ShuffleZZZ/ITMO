package ru.itmo.wm4.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import ru.itmo.wm4.domain.Notice;

public interface NoticeRepository extends JpaRepository<Notice, Long> {

}
