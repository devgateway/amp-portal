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
      },
      searchFiltersPrimarySectorsEnabled: {
        type: 'boolean',
        default: true
      },
      searchPrimarySectorTitle: {
        type: 'string',
        default: 'Primary Sector'
      },
      searchPrimarySectorPlaceHolder: {
        type: 'string',
        default: 'Primary Sector'
      },
      searchFiltersSecondarySectorsEnabled: {
        type: 'boolean',
        default: true
      },
      searchSecondarySectorTitle: {
        type: 'string',
        default: 'Secondary Sector'
      },
      searchSecondarySectorPlaceHolder: {
        type: 'string',
        default: 'Secondary Sector'
      },
      searchFiltersLocationEnabled: {
        type: 'boolean',
        default: true
      },
      searchLocationTitle: {
        type: 'string',
        default: 'Locations'
      },
      searchLocationPlaceHolder: {
        type: 'string',
        default: 'Locations'
      },
      searchDonorEnabled: {
        type: 'boolean',
        default: true
      },
      searchDonorTitle: {
        type: 'string',
        default: 'Donor Agency'
      },
      searchDonorPlaceHolder: {
        type: 'string',
        default: 'DonorAgency'
      }
    }
    ,
    edit: BlockEdit,
    save: BlockSave,
  }
)
;
