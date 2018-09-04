# The following software is a pre-requisite to be able to run the AMP Public portal

1. Apache HTTP Server (2.4 version)
2. PHP (5.5 version)
3. PostgreSQL (9.4 version)

After you have installed you need to checkout the code from the git repositoring and follow the steps below to configure it.


## Adding a virtual host 
```bash

<VirtualHost *:80>
  ServerName amp.example.org
  ServerAlias www.amp.example.org

  # Enable proxy requests.
  ProxyRequests Off
  ProxyPreserveHost On

  # Redirect domain root to the portal homepage.
  RewriteEngine On
  RewriteRule ^/$ /portal [R]

  # Map the portal to the Directory and give access.
  Alias /portal "/var/www/amp-cms" #Customize according your installation
  <Directory "/var/www/amp-cms"> #Customize according your installation
    Options Indexes FollowSymLinks MultiViews
    AllowOverride all
    Require all granted
  </Directory>

  # Logging
  ServerSignature Off
  ErrorLog "/var/log/httpd/amp-cms.error.log" #Customize according your installation
  CustomLog "/var/log/httpd/amp-cms.access.log" combined #Customize according your installation
</VirtualHost>
```

## PHP configuration that needs to be change
```bash
; Search for these settings and update the values.
max_execution_time = 60
memory_limit = 512M
post_max_size = 128M
upload_max_filesize = 128M
```

## Install the portal with DRUSH

## Install the portal
1. Install a new environment from scratch.

```bash
# Install a basic Drupal prepared for the AMP CMS. (the directory we have cloned out from git)
drush install 
# if you get a command not found error you should add $INSTALL_DIR/drush/drush to the system path. Also notice that PHP has
# to be available in path too.
# Here you need to enter the DB credentials
  
# Convert the empty Drupal installation into an AMP CMS.
drush setup
# Here you will see several status updates (it will take several minutes) and then the CMS has finished installing.
  
# Because of some issue in the setup process there are several "not defined" warnings but you can fix them by running:
drush usr task/revert.features.php -y
```

2. Log in with the oneUser username and Create a new user and give it the "admin user" role.
4. Configure the AMP API in order to be able to retrieve AMP Date
  a. Click in the upper right corner, the settings link 
  b. Click on API Settings
  c. Enter the AMP api URL
5. Log out and forget about the oneUser, you should not use that user ever again!
6. est and see if your new environment is working, if you have any question feel free to contact us
