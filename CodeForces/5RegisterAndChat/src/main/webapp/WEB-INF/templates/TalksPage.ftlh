<#import "common.ftl" as c>

<@c.page>
<div class="form-box">
    <div class="header">Send Message</div>
    <div class="body">
        <form method="post" action="/talks">
            <input type="hidden" name="action" value="talks">
            <div class="field">
                <div class="name">
                    <label for="target">Name</label>
                </div>
                <div class="value">
                    <input id="target" name="target" value="${target!}"/>
                </div>
            </div>
            <div class="field">
                <div class="name">
                    <label for="text">Text</label>
                </div>
                <div class="value">
                    <input id="text" name="text" value="${text!}"/>
                </div>
            </div>
            <div class="button-field">
                <input type="submit" value="Send">
            </div>
            <#if error??>
            <div class="error">
                ${error}
            </div>
            </#if>
        </form>
    </div>
    <#if error??>
    <#else>
    <section>
        <div class="header">
            Chat
        </div>
        <#list talks as talk>
            <ul>
                ${talk.text} by ${talk.source} to ${talk.target}
                <div class="date">${talk.time} </div>
            </ul>
        </#list>
    </section>
    </#if>
</div>
</@c.page>
