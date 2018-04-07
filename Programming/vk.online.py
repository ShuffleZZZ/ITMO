import urllib.request

output=open('out.txt', 'w')
url="https://vk.com/id368160669"
get=urllib.request.Request(url)
get1=urllib.request.urlopen(get)
get2=get1.read()
if "offline" in str(get2):
    print("offline")
else:
    print("online")