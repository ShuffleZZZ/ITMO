package ru.itmo.wp.servlet;

import ru.itmo.wp.util.ImageUtils;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.http.HttpFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Base64;
import java.util.Random;

public class CaptchaFilter extends HttpFilter {
    private static String generateForm(Integer captchaData, String redirectTo) {
        String encodedImage = Base64.getEncoder().encodeToString(ImageUtils.toPng(captchaData.toString()));
        String[] html = {"<!DOCTYPE html>\n" +
                "<html lang=\"en\">\n" +
                "<head>\n" +
                "<body>\n" +
                "  <div class=\"captcha-form\">\n" +
                "    <img src=\"data:image/png;base64, ",

                "\">\n      <form class=\"captcha-form\" method=\"get\" action=\"",

                "\">\n      <label for=\"captcha__answer\">Enter number:</label>\n" +
                "       <input name=\"captcha\" id=\"captcha_answer\">\n" +
                "       </form>\n" +
                "       </div>\n" +
                "</body>\n" +
                "</html>"};
        return html[0] + encodedImage + html[1] + redirectTo + html[2];
    }
    @Override
    protected void doFilter(HttpServletRequest request, HttpServletResponse response, FilterChain chain) throws IOException, ServletException {
        HttpSession session = request.getSession();
        if (session.getAttribute("PassedCaptcha") == null) {
            session.setAttribute("PassedCaptcha", "no");
        }
        if (session.getAttribute("PassedCaptcha").toString().equals("no")) {
            if (session.getAttribute("Captcha") == null) {
                session.setAttribute("Captcha", Integer.toString(new Random().nextInt(900) + 100));
            }
            String input = request.getParameter("captcha");
            if (input != null && input.equals(session.getAttribute("Captcha").toString())) {
                session.setAttribute("PassedCaptcha", "yes");
                response.sendRedirect(request.getRequestURI());
                return;
            }
            session.setAttribute("Captcha", new Random().nextInt(900) + 100);
            OutputStream outputStream = response.getOutputStream();
            outputStream.write(generateForm((int) session.getAttribute("Captcha"), request.getRequestURI()).getBytes());
            outputStream.flush();
        } else {
            chain.doFilter(request, response);
        }
    }
}