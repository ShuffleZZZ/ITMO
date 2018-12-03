<#-- @ftlvariable name="message" type="java.lang.String" -->

<#import "common.ftl" as c>

<@c.page>
    <#if message??>
        <h4>${message}</h4>
    </#if>

    <h1>Welcome to the index page</h1>
</@c.page>