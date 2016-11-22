
# AMP Portal Environment Upgrade Instructions

Follow these steps for upgrading AMP Portal Environments:


## Moving from the old SVN repo to GIT
If you switching from SVN you can clone a new directory and move the site files to the new directory and then update
the web server to point the `web` directory instead of the project root directly.

0.  First you should read the install instructions for new environments for various gotchas.

1.  Backup the portal database and files:
    ```
    # Go to the portal root directory.
    cd /var/www/amp212-portal

    # Backup the site files and database in a safe place.
    make backup DIR=~/backups/
    ```

2.  Clone the new repository in a different place.
    ```
    mkdir -p /var/www/amp212-portal-NEW/
    cd /var/www/amp212-portal-NEW/
    git clone --branch=support/v2.10 git@github.com:devgateway/amp-portal.git .
    ```

3.  Copy the configuration and site files from the old portal.
    ```
    # Make sure the files are writable by the user.
    chmod -R +w /var/www/amp212-portal/sites/default/

    # Copy the portal configuration (i.e. database credentials).
    # Please note the extra `web` directory in path.
    cp /var/www/amp212-portal/sites/default/drushrc.custom.php /var/www/amp212-portal-NEW/web/sites/default/
    cp /var/www/amp212-portal/sites/default/settings.custom.php /var/www/amp212-portal-NEW/web/sites/default/

    # Copy the site files and keep the files owner and permissions (required for linux).
    cp -a /var/www/amp212-portal-OLD/sites/default/files /var/www/amp212-portal-NEW/web/sites/default/
    ```

4.  [OPTIONAL] Move the old portal codebase out of the way if you plan to use the same directory for thew new website.
    > NOTE: You should keep the directory until you are sure that the new installation is working and you don't need to
    >       revert the changes.

5.  Update the web server configuration to point to the `web` directory inside the project root.

6.  Continue with the normal update process and make sure the new installation is working properly.
    TODO: Add link to the normal update process.

7.  Cleanup the old files and backups once you are sure the upgrade is complete.

8.  Congratulations, you are done!
