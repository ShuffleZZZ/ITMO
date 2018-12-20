<#import "./common.ftlh" as c>

<@c.page>
    <div class="datatable">
        <div class="caption">Users</div>
        <table>
            <thead>
                <tr>
                    <th>ID</th>
                    <th>Login</th>
                    <th>Created At</th>
                    <th>Change Access</th>
                </tr>
            </thead>
            <tbody>
                <#list users as user>
                    <tr>
                        <td>${user.id}</td>
                        <td><a href="/user/${user.id}">${user.login}</a></td>
                        <td>${user.creationTime}</td>
                        <td>
                            <form method="post" action="/changeAccess">
                                <input type="hidden" name="id" value="${user.id}">
                                <input type="submit" name="status" value="<#if user.disabled>Enable<#else>Disable</#if>">
                            </form>
                        </td>
                    </tr>
                </#list>
            </tbody>
        </table>
    </div>
</@c.page>