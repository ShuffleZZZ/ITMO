__author__ = 'glagolev'

import urllib.request
url = "https://pp.userapi.com/c639223/v639223753/500ee/WKAcXQsITNo.jpg"
img = urllib.request.urlopen(url).read()
out = open("img.jpg", "wb")
out.write(img)
out.close()
