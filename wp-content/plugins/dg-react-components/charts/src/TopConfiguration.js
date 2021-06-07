/* eslint-disable react/react-in-jsx-scope */
import { PanelBody, PanelRow, SelectControl } from '@wordpress/components';
import { __ } from '@wordpress/i18n';
import { useEffect } from "react";


const TopConfiguration = ({
                            app,
                            height,
                            topChartType,
                            topChartColumnCount,
                            setAttributes,
                            initialOpen
                          }) => {

  const topChartTypeItems = [
    { value: 'do', label: 'Donor Agency' },
    { value: "ro", label: 'Responsible Organization' },
    { value: "ba", label: 'Beneficiary Agency' },
    { value: "ia", label: 'Implementing Agency' },
    { value: "ea", label: 'Executing Agency' },
    { value: "re", label: 'Administrative Level 1' },
    { value: "ps", label: 'Primary Sector' },
    { value: "dg", label: 'Donor Group' }
  ]
  const topChartColumnsItems = [
    { value: 3, label: '3' },
    { value: 4, label: '4' },
    { value: 5, label: '5' },
    { value: 6, label: '6' },
    { value: 7, label: '7' },
    { value: 8, label: '8' }
  ]


  return (
    <PanelBody initialOpen={false} title={__("Top charts configuration")}>
      <PanelRow>
        <SelectControl
          label={__('Top Chart Type')}
          value={[topChartType]}
          onChange={(value) => {
            setAttributes({ topChartType: value })
          }}
          options={topChartTypeItems}
        />
      </PanelRow>

      <PanelRow>
        <SelectControl
          label={__('Top Chart Column count')}
          value={[topChartColumnCount]}
          onChange={(value) => {
            setAttributes({ topChartColumnCount: value })
          }}
          options={topChartColumnsItems}
        />
      </PanelRow>
    </PanelBody>

  )

}

export default TopConfiguration