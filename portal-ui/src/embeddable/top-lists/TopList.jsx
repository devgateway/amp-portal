import React, { Component } from 'react';
import { Button, Table, Menu, Icon, Popup } from "semantic-ui-react";
import EllipsisText from 'react-ellipsis-text';
import PropTypes from 'prop-types';
import './TopList.scss';
import hash from 'object-hash';
import { formatKMB, getGlobalSettings } from "../chart/utils";
import { injectIntl } from "react-intl";
import { connect } from "react-redux";
import { AMP_PREVIEW_URL } from "../Constants";

const TopList = (props) => {
  const {
    labels,
    data,
    currency,
    fields,
    topSize,
    intl,
    settings,
    numberFields,
    linkFields,
    identity,
    linkOwnColumn,
    isBigTable
  } = props;
  const globalSettings = getGlobalSettings(settings);
  const formatter = formatKMB(intl, globalSettings.precision + 1, globalSettings.decimalSeparator, false, null);
  const ellipsis = (d, f, ellipsisLength) => {
    return <EllipsisText
      text={d[f] ? d[f] : ''}
      length={ellipsisLength} tail={"..."} />;
  }
  //TODO GALI TO STYLE LINKS
  const rowCell = (d, f) => {
    if (topSize === 'top5' && !numberFields.includes(f)) {
      if (linkFields.includes((f))) {
        return <Button as='a' href={`${process.env.REACT_APP_AMP_URL}${AMP_PREVIEW_URL}${d['activity-id']}`}
                       target="_blank">{ellipsis(d, f, 20)}</Button>
      } else {
        return ellipsis(d, f, 20);
      }
    } else {
      if (numberFields.includes(f) && !isBigTable) {
        return `${formatter(d[f + '-raw'])} ${currency}`;
      }
      return ellipsis(d, f, 50);
    }
  }
  //TODO GALI TO ADJUST TOOLTIP STYLE
  const header = () =>
    labels.tooltip && labels.tooltip.length > 0 ?
      <Popup basic content={labels.tooltip} trigger={<h3>{labels.title}</h3>} /> : <h3>{labels.title}</h3>;
  const tableBody = () =>
    data.data.map((d) =>
      (
        <Table.Row key={hash(d[identity])}>
          {fields.map(f => <Table.Cell> {rowCell(d, f)} </Table.Cell>)}
        </Table.Row>))

  const tableHeaders = () => {
    const header = [];
    if (linkOwnColumn) {
      header.push(['']);
    }
    const mergedHeader = [...header, ...fields.map(f => {
      return <Table.HeaderCell>{data.headers[f]}</Table.HeaderCell>
    })];
    return mergedHeader;
  }
  return <div className={"top-list"}>
    <div className="list-header">
      {header()}
      <Button floated='right'>Download XLS</Button>
    </div>
    <div className="description">{labels.description}</div>

    <Table celled>
      {isBigTable && (
        <Table.Header>
          <Table.Row>
            {tableHeaders()}
          </Table.Row>
        </Table.Header>
      )}
      <Table.Body>
        {tableBody()}
      </Table.Body>
    </Table>
    <Button className="full-list-link">View Full List</Button>
  </div>;
}

const mapStateToProps = (state) => {
  return {
    settings: state.getIn(['data', ...['amp-settings'], 'data'])
  }
}
const mapActionCreators = {};
export default connect(mapStateToProps, mapActionCreators)(injectIntl(TopList));
TopList.propTypes = {
  numberFields: PropTypes.array,
  linkOwnColumn: PropTypes.bool,
  isBigTable: PropTypes.bool,
}
TopList.defaultProps = { numberFields: [], linkOwnColumn: false, isBigTable: false }

