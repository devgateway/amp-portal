<?php

// Update module weight, because we need to fix locale URL alterations.
db_update('system')
  ->fields(array('weight' => 5))
  ->condition('name', 'ampapi')
  ->execute();
