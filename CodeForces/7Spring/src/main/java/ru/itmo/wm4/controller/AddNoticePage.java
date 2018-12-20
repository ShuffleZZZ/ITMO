package ru.itmo.wm4.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.WebDataBinder;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.InitBinder;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import ru.itmo.wm4.form.NoticeCredentials;
import ru.itmo.wm4.form.validator.NoticeCredentialsAddValidator;
import ru.itmo.wm4.service.NoticeService;

import javax.servlet.http.HttpSession;
import javax.validation.Valid;

@Controller
public class AddNoticePage extends Page {
    private final NoticeService noticeService;
    private final NoticeCredentialsAddValidator noticeCredentialsAddValidator;

    public AddNoticePage(NoticeService noticeService, NoticeCredentialsAddValidator noticeCredentialsAddValidator) {
        this.noticeService = noticeService;
        this.noticeCredentialsAddValidator = noticeCredentialsAddValidator;
    }

    @InitBinder("NoticeCredentials")
    public void initRegisterFormBinder(WebDataBinder binder) {
        binder.addValidators(noticeCredentialsAddValidator);
    }

    @GetMapping(path = "/addNotice")
    public String addNoticeGet(Model model) {
        model.addAttribute("addNoticeForm", new NoticeCredentials());
        return "AddNoticePage";
    }

    @PostMapping(path = "/addNotice")
    public String addNoticePost(@Valid @ModelAttribute("addNoticeForm") NoticeCredentials addNoticeForm,
                                BindingResult bindingResult, HttpSession httpSession) {
        if (bindingResult.hasErrors()) {
            return "AddNoticePage";
        }

        noticeService.save(addNoticeForm);
        return "redirect:/";
    }
}