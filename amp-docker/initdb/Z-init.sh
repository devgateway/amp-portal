#!/bin/bash

psql -U amp -c "UPDATE amp_global_settings SET settingsvalue = 'false' WHERE settingsname = 'Machine Translation Enabled';"
