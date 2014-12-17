<?php

// Enable default CAPTCHA.
$forms = array(
  'contact_entityform_edit_form'
);
foreach ($forms as $form_id) {
  db_merge('captcha_points')
    ->key(array('form_id' => $form_id))
    ->fields(array('module' => NULL, 'captcha_type' => 'default'))
    ->execute();
}
