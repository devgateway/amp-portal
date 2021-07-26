import { __ } from '@wordpress/i18n';
import { registerBlockType } from '@wordpress/blocks';
import BlockSave from "./BlockSave";
import BlockEdit from "./BlockEdit";
import { Generic } from '../icons/index'

registerBlockType(process.env.BLOCKS_NS + '/activities-search',
  {
    title: __('Activities search Component'),
    icon: Generic,
    category: process.env.BLOCKS_CATEGORY,
    apiVersion: 2,
    attributes: {
      height: {
        type: 'number',
        default: 500,
      },
      searchTitle: {
        type: 'string',
        default: 'Search Activities',
      },
      searchDescription: {
        type: 'string',
        default: 'Search keywords with activities',
      },
      searchButton: {
        type: 'String',
        default: 'Search'
      },
      searchHint: {
        type: 'string',
        default: 'e.g Writing, coding or design job',
      },
      searchTooltip: {
        type: 'string',
        default: ''
      },
      searchExtendedSlug: {
        type: 'string',
        default: 'search-results'
      },
      searchType: {
        type: 'string',
        default: 'simpleSearch'
      }
    }
    ,
    edit: BlockEdit,
    save: BlockSave,
  }
)
;
