import React, { Component, useState } from 'react';
import { ResponsiveBar } from '@nivo/bar';
import PropTypes from 'prop-types';
import { injectIntl } from "react-intl";
import { formatKMB } from "./utils";
import SimpleLegend from "./legends/SimpleLegend";
import { Grid } from "semantic-ui-react";
import './Top.scss';
import ToolTip from "./legends/ToolTip";
import { getColor } from './TopChartUtils';


const Top = ({ colors, height, options, intl, f, legends, measure }) => {

  const getLabel = (item) => {
    return formatValue(item.data.value);
  }

  const formatValue = (value) => {
    const globalSettings = {};
    // TODO integrate with amp settings
    globalSettings.precision = 3;
    globalSettings.decimalSeparator = '.';
    const formatter = formatKMB(intl, globalSettings.precision, globalSettings.decimalSeparator, false, null);
    return formatter(value);
  }
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

  const globalSettings = {};
  globalSettings.groupSeparator = ',';
  globalSettings.numberDivider = 1
  globalSettings.numberDividerDescriptionKey = '';
  globalSettings.precision = 3;
  globalSettings.decimalSeparator = '.';
  const barHeight = `${height}px`;
  return (
    <Grid className={"container top-chart"}>
      <Grid.Row>
        <Grid.Column computer={10} mobile={16}>{legends.title}</Grid.Column>
        <Grid.Column computer={6} mobile={16}>{`${formatValue(options.total)} ${options.currency}`}</Grid.Column>
      </Grid.Row>
      <div className={'inner'}>
        <SimpleLegend
          data={options.values}
          title={legends.title}
          filter={filter}
          colors={colors}
          toggle={toggle}
        />
        <div style={{ height: barHeight }}>
          <ResponsiveBar
            data={applyFilter(options.values)}
            colors={item => getColor(item, colors)}
            label={getLabel}
            enableGridY={false}
            axisTop={null}
            axisRight={null}
            axisBottom={null}
            axisLeft={null}
            margin={{
              top: 20, right: 10, bottom: 0, left: 10
            }}
            labelFormat={d => (<tspan y={-5}>{`${d}`}</tspan>)}
            tooltip={(e) => (
              <ToolTip
                color={e.color}
                titleLabel={e.data.name}
                formattedValue={e.data.formattedAmount}
                value={e.data.value}
                total={options.total}
                id={e.data.id}
                currencyCode={options.currency}
                globalSettings={globalSettings}
              />
            )}

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
  );
}

Top.propTypes = {
  data: PropTypes.object.isRequired,
  globalSettings: PropTypes.object.isRequired,
  translations: PropTypes.object.isRequired,
  settings: PropTypes.object.isRequired
};

export default injectIntl(Top)