<?php

// Provide a list of modules to be installed.
$modules = array(
  'contextual',

  'contentblock',
  'elements',
);
_us_module__install($modules);

// Prepare a list of features to be installed.
$feature_names = array(
  'ampcontentblock',
);
_us_features__install($feature_names);

// Delete all links from menu.
_us_menu__delete_links('user-menu');

$link = array(
  'link_path' => 'admin/content',
  'link_title' => 'Content',
  'weight' => -45,
);
_us_menu__create_link($link, 'user-menu');

$link = array(
  'link_path' => 'admin/people',
  'link_title' => 'People',
  'weight' => -44,
);
_us_menu__create_link($link, 'user-menu');

$link = array(
  'link_path' => 'admin/settings',
  'link_title' => 'Settings',
  'weight' => -43,
);
_us_menu__create_link($link, 'user-menu');
