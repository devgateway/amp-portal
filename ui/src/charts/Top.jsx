import React, { Component } from 'react';
import { ResponsiveBar } from '@nivo/bar';
import PropTypes from 'prop-types';
import { injectIntl } from "react-intl";
import { formatKMB } from "./utils";
import SimpleLegend from "./legends/SimpleLegend";
import { Grid } from "semantic-ui-react";
import './Top.scss';
import ToolTip from "./legends/ToolTip";

// import ToolTip from "./legends/ToolTip";

class Top extends Component {
  // eslint-disable-next-line class-methods-use-this
  getColor(item) {
    return colors[item.index];
  }

  getLabel(item) {
    return this.formatValue(item.data.value);
  }

  formatValue(value) {
    const { intl } = this.props;
    const globalSettings = {};
    // TODO integrate with amp settings
    globalSettings.precision = 3;
    globalSettings.decimalSeparator = '.';
    const formatter = formatKMB(intl, globalSettings.precision, globalSettings.decimalSeparator, false, null);
    return formatter(value);
  }

  render() {
    const { options, legends, height } = this.props;
    const globalSettings = {};
    globalSettings.groupSeparator = ',';
    globalSettings.numberDivider = 1
    globalSettings.numberDividerDescriptionKey = '';
    globalSettings.precision = 3;
    globalSettings.decimalSeparator = '.';
    const barHeight =`${height}px`;
    return (
      <Grid className={"container top-chart"}>
        <Grid.Row>
          <Grid.Column computer={10} mobile={16}>{legends.title}</Grid.Column>
          <Grid.Column computer={6} mobile={16}>{`${this.formatValue(options.total)} ${options.currency}`}</Grid.Column>
        </Grid.Row>
        <div className={'inner'}>
          <SimpleLegend
            data={options.values}
            title={legends.title}
            getColor={this.getColor.bind(this)}
          />
          <div style={{ height: barHeight }}>
            <ResponsiveBar
              data={options.values}
              colors={this.getColor.bind(this)}
              label={this.getLabel.bind(this)}
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
}

const colors = ['rgba(90, 153, 199, 1)',
  'rgba(195, 214, 238, 1)',
  'rgba(255, 160, 87, 1)',
  'rgba(255, 204, 154, 1)',
  'rgba(99, 184, 99, 1)',
  'rgba(153, 153, 153, 1)',
  'rgba(217, 91, 95, 1)',
  'rgba(253, 170, 170, 1)',
  'rgba(166, 133, 196, 1)',
  'rgba(206, 189, 218, 1)',

];

Top.propTypes = {
  data: PropTypes.object.isRequired,
  globalSettings: PropTypes.object.isRequired,
  translations: PropTypes.object.isRequired,
  settings: PropTypes.object.isRequired
};

export default injectIntl(Top)