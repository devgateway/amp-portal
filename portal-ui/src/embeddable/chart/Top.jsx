import React, { useState } from 'react';
import { ResponsiveBar } from '@nivo/bar';
import { injectIntl } from "react-intl";
import { formatKMB, getGlobalSettings } from "./utils";
import SimpleLegend from "./legends/SimpleLegend";
import { Grid } from "semantic-ui-react";
import './Top.scss';
import ToolTip from "./legends/ToolTip";
import { getColor } from './TopChartUtils';
import { BoxLegendSvg } from "@nivo/legends";
import { linearGradientDef } from "@nivo/core";
import { connect } from "react-redux";


const Top = ({
               colors, options, intl, legends, layout = "vertical", showLegend = true,
               padding = 0.1, barHeight, settings
             }) => {
  const globalSettings = getGlobalSettings(settings);
  const getLabel = (item) => {
    return formatValue(item.data.value);
  }

  const formatValue = (value) => {
    debugger;
    const formatter = formatKMB(intl, 3, globalSettings.decimalSeparator, false, null);
    const formattedValue = formatter(value);
    return formattedValue;
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
  const BarLegend = ({ height, legends, width }) => (
    <React.Fragment>
      {legends.map(legend => (
        <BoxLegendSvg
          key={JSON.stringify(legend.data.map(({ id }) => id))}
          {...legend}
          containerHeight={height}
          containerWidth={width}
        />
      ))}

    </React.Fragment>
  );
  return (
    <Grid className={"container top-chart"}>
      {showLegend && <Grid.Row>
        <Grid.Column computer={10} mobile={16}>{legends.title}</Grid.Column>
        <Grid.Column computer={6} mobile={16}>{`${formatValue(options.total)} ${options.currency}`}</Grid.Column>
      </Grid.Row>
      }
      <div className={'inner'}>
        {showLegend && <SimpleLegend
          data={options.values}
          title={legends.title}
          filter={filter}
          colors={colors}
          toggle={toggle}
        />}
        <div style={{ height: barHeight }}>
          <ResponsiveBar
            data={applyFilter(options.values)}
            colors={item => getColor(item, colors)}
            label={getLabel}
            layers={["grid", "axes", "bars", "markers", BarLegend, 'annotations']}
            enableGridY={false}
            axisTop={null}
            layout={layout}
            padding={padding}
            axisRight={null}
            axisBottom={null}
            axisLeft={null}
            margin={{
              top: 20, right: 10, bottom: 0, left: 10
            }}
            labelFormat={d => <tspan y={-5}>{`${d}`}</tspan>
            }
            defs={[
              linearGradientDef('gradientA', [
                { offset: 0, color: 'inherit' },
                { offset: 100, color: 'inherit', opacity: 0 },
              ])
            ]}
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
const mapStateToProps = (state) => {
  return {
    settings: state.getIn(['data', ...['amp-settings'], 'data'])
  }
}


const mapActionCreators = {};

export default connect(mapStateToProps, mapActionCreators)(injectIntl(Top));
