
#!/bin/bash
su wordpress
wp option update home '$1'
wp option update siteurl '$1'
exit
