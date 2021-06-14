import { __ } from '@wordpress/i18n';
import { registerBlockType } from '@wordpress/blocks';
import BlockSave from "./BlockSave";
import BlockEdit from "./BlockEdit";
import { Chart } from '../../icons'

registerBlockType('dg-components/chart',
  {
    title: __('Dg Data Chart', 'dg-components'),
    icon: Chart,
    category: 'react-blocks',
    apiVersion: 2,
    attributes: {
      height: {
        type: 'number',
        default: 500,
      },

      type: {
        type: 'string',
        default: "bar",
      },
      source: {
        type: 'string',
        default: 'do/5',
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
      topChartType: {
        type: 'String',
        default: 'do'
      },

      topChartColumnCount: {
        type: 'String',
        default: '5'
      },
      fundingType: {
        type: 'String',
        default: 'ftype'
      },
      groupMode: {
        type: 'String',
        default: 'grouped',
      },
      mode: {
        type: 'String',
        default: "chart"
      },


      dualMode: {
        type: "Boolean",
        default: false
      },
      toggleInfoLabel: {
        type: 'String',
        default: "Info Graphic"
      },
      toggleChartLabel: {
        type: 'String',
        default: "Chart"
      },
      chartTitle: {
        type: 'String',
        default: "Chart title"
      },
      chartDescription: {
        type: 'String',
        default: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam sit amet lectus ut " +
          "neque blandit ultricies."
      },

      legendPosition: {
        type: 'String',
        default: "right"
      },
      legendsWidth: {
        type: 'mumeric',
        default: 100
      },
      showLegends: {
        type: 'boolean',
        default: true
      },
      app: {
        type: 'String',
        default: "top"
      },
      measure: {
        type: 'String',
        default: "Actual Commitments"
      },
      params: {
        type: Object,
        default: {}
      },
      format: {
        type: Object,
        default: { "style": "percent", "minimumFractionDigits": 1, "maximumFractionDigits": 1 }
      },
      tickRotation: {
        type: 'mumeric',
        default: 0
      },
      tickColor: {
        type: "String",
        default: "rgb(0,0,0)"
      },
      keys: {
        type: "Array",
        default: []
      },
      formatStyle: {
        type: "String",
        default: "Percent"
      }
      ,
      decimalPoints: {
        type: "Numeric",
        default: 2
      }
      ,
      currency: {
        type: "String",
        default: ""
      }
      ,
      yearFilter: {
        type: "String",
        default: ""
      },
      dateFrom: {
        type: "numeric",
        default: 2010
      },
      dateTo: {
        type: "numeric",
        default: 2030
      },

    }
    ,
    edit: BlockEdit,
    save: BlockSave,
  }
)
;
