<?php

// Install slider module and revert features.
$modules = array(
  'ampet_slide',
);
_us_module__install($modules);
_us_features__revert_all();
