<?php

/**
 * Plugin Name: Tobacco Control Data Initiative UI Components
 * Plugin URI:
 * Description: Custom UI Components.
 * Version: 1.0.0
 * Author: Sebastian Dimunzio
 *
 * @package gutenberg-examples
 */

defined( 'ABSPATH' ) || exit;

function add_custom_block_categories( $categories, $post ) {
	return array_merge(
		$categories,
		array(
			array(
				'slug' => 'tcdi-blocks',
				'title' => __( 'TCDI Blocks', 'React Blocks' ),
			),
		)
	);
}
add_filter( 'block_categories', 'add_custom_block_categories', 10, 2);
include 'post-carousel/index.php';
include 'page-gallery/index.php';
include 'charts/index.php';
include 'filter/index.php';
include 'tabbed-posts/index.php';

#include 'block-styles/index.php';
