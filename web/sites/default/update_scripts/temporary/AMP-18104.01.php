<?php

// Prepare a list of features to be installed.
$feature_names = array(
  'ampcontentblock',
  'ampet_blog',
  'ampet_page',
  'ampfileentity',

  'amphomepage',
  'amppermissions',
  'ampsettings',
  'ampviewsettings',
);
_us_features__install($feature_names);

// Change site homepage.
variable_set('site_frontpage', 'homepage');


// Delete all links from menu.
_us_menu__delete_links('main-menu');

// Add "Homepage" link to the main menu.
$link = array(
  'link_path' => '<front>',
  'link_title' => 'Homepage',
  'weight' => -20,
);
_us_menu__create_link($link, 'main-menu');

// Add "Blog" link to the main menu.
$link = array(
  'link_path' => 'blog',
  'link_title' => 'Blog',
  'weight' => 10,
);
_us_menu__create_link($link, 'main-menu');
