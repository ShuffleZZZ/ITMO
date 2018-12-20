<#import "./common.ftlh" as c>

<@c.page>
    <#if userPage??>
        <article>
            <div class="title">${userPage.login}</div>
            <div class="information">user/${userPage.id}</div>
            <div class="body">
                <p>Registered ${userPage.creationTime}</p>
            </div>
        </article>
    <#else>
        <article>
            <div class="title">No Such User</div>
        </article>
    </#if>
</@c.page>