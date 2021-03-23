import {__} from '@wordpress/i18n';
import {registerBlockType} from '@wordpress/blocks';
import BlockSave from "./BlockSave";
import BlockEdit from "./BlockEdit";

registerBlockType('tcdi-components/chart',
    {
        title: __('Data Chart', 'tcdi-components'),
        icon: 'admin-site-alt',
        category: 'tcdi-blocks',
        apiVersion: 2,
        attributes: {
            height: {
                type: 'number',
                default: 500,
            },
            width: {
                type: 'number',
                default: 900,
            },
            type: {
                type: 'string',
                default: "bar",
            },
            source: {
                type: 'string',
                default: 'gender/smoke',
            },
            bottomLegend: {
                type: 'string',
                default: "Bottom Legends",
            }
            ,
            leftLegend: {
                type: 'string',
                default: "Left Legends",
            },
            scheme: {
                type: 'string',
                default: 'nivo'
            },

            colorBy: {
                type: 'String',
                default: 'index'
            },
            level1: {
                type: 'String',
                default: 'gender'
            },

            level2: {
                type: 'String',
                default: 'race'
            },

            level3: {
                type: 'String',
                default: 'smoke'
            },
            groupMode:{
                type:'String',
                default:'stacked',
            },
            mode:{
                type:'String',
                default:"chart"
            },
            dualMode:{
                type:"Boolean",
                default:false
            }

        }
        ,
        edit: BlockEdit,
        save: BlockSave,
    }
)
;
