import React from 'react';
import './DonorScoreCard.scss';
import { ResponsiveBar } from "@nivo/bar";
import { injectIntl } from "react-intl";
import ToolTip from "../legends/ToolTip";
import { TooltipWrapper } from '@nivo/tooltip';

const DonorScoreCard = (props) => {
  const { options } = props;


  const getPercentageColor = (item) => {
    const GREEN = '#52a963';
    const YELLOW = '#fadd45';
    const RED = '#eb6468';
    const GREY = '#808080';
    const SHADE = 30;
    const DISABLED = '#e2e7ee';
    switch (item.indexValue) {
      case "amp.on-time":
        if (item.id === "one") {
          return GREEN;
        } else {
          return DISABLED;
        }
      case "amp.validation":
        if (item.id === "one") {
          return YELLOW;
        } else {
          return DISABLED;
        }
      case "amp.late":
        if (item.id === "one") {
          return RED;
        } else {
          return DISABLED;
        }
      case "amp.no-updates":
        if (item.id === "one") {
          return GREY;
        } else {
          return DISABLED;
        }
      default:
        return '#000000'

    }
  }
  const { legends } = props;
  return (<div className={"donor-scorecard-chart"}>
    <h3>{legends.title}</h3>
    <div className="description">{legends.chartDescription}
    </div>
    <div className="data-wrapper">
      <div style={{ height: "100px", width: "90%" }}>
        <ResponsiveBar
          data={options.values.sort((a, b) => b.index - a.index)}
          keys={["one", "two"]}
          indexBy="id"
          margin={{
            top: 0,
            right: 32,
            bottom: 30,
            left: 90
          }}
          colors={getPercentageColor}
          padding={0.2}
          layout="horizontal"
          borderColor="inherit:darker(1.6)"
          enableLabel={false}
          enableGridX={false}
          enableGridY={false}
          axisLeft={{
            tickSize: 2,
            tickPadding: 2,
            tickRotation: 0,
            legend: "",
            legendPosition: "middle",
            renderTick: ({
                           textAnchor,
                           textBaseline,
                           textX,
                           textY,
                           value,
                           x,
                           y
                         }) => {
              return (
                <g transform={`translate(${x},${y})`}>
                  <text
                    alignmentBaseline={textBaseline}
                    textAnchor={textAnchor}
                    transform={`translate(${textX},${textY})`}
                  >
                    <tspan
                      style={{ fontSize: `${legends.scoreCardLegendsSize}px` }}>{legends.scoreCardLegends[value].label}</tspan>
                  </text>
                </g>
              );
            }
          }}


          axisRight={{
            tickSize: 2,
            tickPadding: 2,
            tickRotation: 0,
            legend: "",
            legendPosition: "middle",
            renderTick: ({
                           textAnchor,
                           textBaseline,
                           textX,
                           textY,
                           value,
                           x,
                           y
                         }) => {
              return (
                <g transform={`translate(${x},${y})`}>
                  <text
                    alignmentBaseline={textBaseline}
                    textAnchor={textAnchor}
                    transform={`translate(${textX},${textY})`}
                  >
                    <tspan
                      style={{ fontSize: `${legends.scoreCardLegendsSize}px` }}>
                      {`${/*options.values.find(o => o.id === value).one*/100}%`}</tspan>
                  </text>
                </g>
              );
            }
          }}
          tooltip={(e) => {
            const item = { ...e };
            item.id = 'one';
            return (
              <TooltipWrapper anchor="top" position={[100, 0]}>
                <ToolTip
                  color={getPercentageColor(item)}
                  titleLabel={legends.scoreCardLegends[e.indexValue].label}
                  value={legends.scoreCardLegends[e.indexValue].tooltip}
                  id={e.data.id}
                  currencyCode={options.currency}
                  amountsIn={false}
                />
              </TooltipWrapper>
            );
          }}
          theme={{
            tooltip: {
              container: {
                width: "200px",
                padding: '1px',
                borderRadius: 'none',
                boxShadow: 'none',
                background: 'none'
              }
            },
            axis: {
              domain: {
                line: {
                  stroke: "#a9acbe",
                  strokeWidth: 0
                }
              }
            },
            grid: {
              line: {
                stroke: "#e7e8ec",
                strokeWidth: 0
              }
            }
          }}
          layers={["grid", "axes", "bars", "markers"]}
        />
      </div>
    </div>

    {/*<div
      style="background: white none repeat scroll 0% 0%; color: inherit; font-size: inherit; border-radius: 5px; box-shadow: rgba(0, 0, 0, 0.25) 0px 1px 2px; padding: 1px; width: 200px;">
      <div
        style="pointer-events: none; position: absolute; z-index: 10; top: 0px; left: 0px; transform: translate(0px);">
        <div>hola hola</div>
      </div>
    </div>*/}
  </div>)
}
export default injectIntl(DonorScoreCard);
