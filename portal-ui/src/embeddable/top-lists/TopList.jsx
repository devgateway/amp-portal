import React, { Component } from 'react';
import { Button, Table, Menu, Icon } from "semantic-ui-react";
import './TopList.scss';
import hash from 'object-hash';

const TopList = (props) => {
  console.log(props);
  const { labels, data, currency, topShowDonorGroup } = props;
  const showHeader = false;
  return <div className={"top-list"}>
    <div className="list-header">
      <h3>{labels.title}</h3>
      <Button floated='right'>Download XLS</Button>
    </div>
    <div className="description">{labels.description}</div>

    <Table celled>
      {showHeader && (
        <Table.Header>
          <Table.Row>
            <Table.HeaderCell>{data.headers[topShowDonorGroup ? 'donor-group' : 'donor-agency']}</Table.HeaderCell>
            <Table.HeaderCell>{data.headers['actual-commitments']}({currency})</Table.HeaderCell>
          </Table.Row>
        </Table.Header>
      )}
      <Table.Body>
        {data.data.map((d) => {
          return (<Table.Row key={hash(d[topShowDonorGroup?'donor-group':'donor-agency'])}>
            <Table.Cell>{d[topShowDonorGroup?'donor-group':'donor-agency']}</Table.Cell>
            <Table.Cell>{d['actual-commitments']}</Table.Cell>
          </Table.Row>)
        })}
      </Table.Body>
    </Table>
    <Button className="full-list-link">View Full List</Button>
  </div>;
}
export default TopList;
