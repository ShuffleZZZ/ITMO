<#import "/spring.ftl" as spring>
<#import "./common.ftlh" as c>

<#macro error field>
    <@spring.bind field/>
    <#list spring.status.errorMessages as error>
        <div class="error">${error}</div>
        <#break/>
    </#list>
</#macro>

<@c.page>
    <#if notice??>
        <div class="notice form-box">
            <div class="header">Notice</div>
            <div class="body">
                ${notice.text?html}
            </div>
            <div class="sign">
                by ${notice.user.login}
            </div>
            <div class="time">
                ${notice.creationTime}
            </div>
            <div class="tags">
                <#list notice.tags as tag>
                    <a href="https://twitter.com/hashtag/${tag.name}">#${tag.name}</a>
                </#list>
            </div>
            <#if user??>
                <section>
                    <div class="add-comment">
                        <div class="header">New Comment</div>
                        <div class="body">
                            <form method="post" action="/notice/${notice.id}">
                                <div class="field">
                                    <div class="name">
                                        <label for="text">Text</label>
                                    </div>
                                    <div class="value">
                                        <textarea id="text" name="text"></textarea>
                                    </div>
                                </div>
                                <div class="button-field">
                                    <input type="submit" value="Add">
                                </div>
                            </form>
                        </div>
                    </div>
                </section>
            </#if>
            <section>
                <div class="comments">
                    <div class="header">Comments</div>
                    <#list notice.comments as comment>
                        <ul>
                            <div class="comment">
                                ${comment.text?html}
                            </div>
                            <div class="sign">
                                by ${comment.user.login}
                            </div>
                            <div class="time">
                                ${comment.creationTime}
                            </div>
                        </ul>
                    </#list>
                </div>
            </section>
        </div>
    <#else>
        <div class="message">
            No such notice found
        </div>
    </#if>
</@c.page>