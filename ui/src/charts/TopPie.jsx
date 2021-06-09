import React, { useState } from 'react'
import { injectIntl } from 'react-intl';
import { ResponsivePie } from '@nivo/pie'
import ToolTip from "./legends/ToolTip";
import { formatKMB, formatNumberWithSettings, getTextWidth } from "./utils";
import { format } from "d3-format";
import { BoxLegendSvg } from "@nivo/legends";
import {
  colorSchemes,
  isCategoricalColorScheme,
  isSequentialColorScheme,
  sequentialColorInterpolators
} from '@nivo/colors'
import { getColor } from './TopChartUtils';
import { Grid } from "semantic-ui-react";
import './TopPie.scss';
import SimpleLegend from "./legends/SimpleLegend";


const TopPie = ({ colors, height, options, intl, f, legends, measure }) => {


  const [filter, setFilter] = useState([])

  const toggle = (id) => {
    const newFilter = filter.slice();
    if (newFilter.indexOf(id) > -1) {
      const index = newFilter.indexOf(id);
      newFilter.splice(index, 1);
    } else {
      newFilter.push(id)
    }
    setFilter(newFilter)
  }

  const applyFilter = (values) => {
    if (filter) {
      return values.filter(d => filter.indexOf(d.id) === -1);
    } else {
      return values
    }
  }

  const formatValue = (value) => {
    const globalSettings = {};
    // TODO integrate with amp settings
    globalSettings.precision = 3;
    globalSettings.decimalSeparator = '.';
    const formatter = formatKMB(intl, globalSettings.precision, globalSettings.decimalSeparator, false, null);
    return formatter(value);
  }
  if (!options || !options.values) {
    return null
  }
  const globalSettings = {};
  globalSettings.groupSeparator = ',';
  globalSettings.numberDivider = 1
  globalSettings.numberDividerDescriptionKey = '';
  globalSettings.precision = 3;
  globalSettings.decimalSeparator = '.';
  return (
    <Grid className={"top-pie"}>
      <Grid.Row>
        <Grid.Column computer={10} mobile={16}>{legends.title}</Grid.Column>
        <Grid.Column computer={6} mobile={16}>{`${formatValue(options.total)} ${options.currency}`}</Grid.Column>
      </Grid.Row>
      <div className={'inner'}>
        {<SimpleLegend
          toggle={toggle}
          data={options.values}
          title={legends.title}
          filter={filter}
          colors={colors}
        />}
        <div style={{ height: height }}>
          <ResponsivePie
            layers={[
              "slices",
              "sliceLabels",
              /*"radialLabels",*/
              "legends"
            ]}
            colors={item => {
              return getColor(item, colors);
            }}
            data={applyFilter(options.values)}
            margin={{ top: 0, right: 0, bottom: 0, left: 0 }}
            innerRadius={0.5}
            padAngle={0.7}
            cornerRadius={3}
            activeOuterRadiusOffset={8}
            borderWidth={1}
            borderColor={{ from: 'color', modifiers: [['darker', 0.2]] }}
            arcLinkLabelsSkipAngle={10}
            arcLinkLabelsTextColor="#333333"
            arcLinkLabelsThickness={2}
            arcLinkLabelsColor={{ from: 'color' }}
            arcLabelsSkipAngle={10}
            arcLabelsTextColor={{ from: 'color', modifiers: [['darker', 2]] }}
            sliceLabel={d => {
              return intl.formatNumber(Math.abs(options.total > 0 ? ((d.value * 100) / options.total) * 100 : 0) / 100, f);
            }}
            tooltip={(e) => {
              return (
                <ToolTip
                  color={e.datum.color}
                  titleLabel={e.datum.data.name}
                  formattedValue={e.datum.data.formattedAmount}
                  value={e.datum.data.value}
                  total={options.total}
                  id={e.datum.data.id}
                  currencyCode={options.currency}
                  globalSettings={globalSettings}
                />
              );
            }}
            theme={{
              tooltip: {
                container: {
                  padding: '1px',
                  borderRadius: '5px',
                  boxShadow: '0 1px 2px rgba(0, 0, 0, 0.25)'
                }
              }
            }}
          />
        </div>
      </div>
    </Grid>
  )
}
export default injectIntl(TopPie)

