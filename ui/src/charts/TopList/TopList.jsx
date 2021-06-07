import React, { Component } from 'react';
import {Button, Table, Menu, Icon} from "semantic-ui-react";
import './TopList.scss';
export default class TopList extends Component {
  render() {
    return <div className={"top-list"}>
            <div className="list-header">
              <h3>Top 5 Donors</h3>
              <Button floated='right'>Download XLS</Button>
            </div>
            <div className="description">Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.</div>

            <Table celled>
              <Table.Header>
                <Table.Row>
                  <Table.HeaderCell>Donor Agency</Table.HeaderCell>
                  <Table.HeaderCell>Acutal Disbursements (USD)</Table.HeaderCell>
                </Table.Row>
              </Table.Header>

              <Table.Body>
                <Table.Row>
                  <Table.Cell>Cell</Table.Cell>
                  <Table.Cell>Cell</Table.Cell>
                </Table.Row>
                <Table.Row>
                  <Table.Cell>Cell</Table.Cell>
                  <Table.Cell>Cell</Table.Cell>
                </Table.Row>
                <Table.Row>
                  <Table.Cell>Cell</Table.Cell>
                  <Table.Cell>Cell</Table.Cell>
                </Table.Row>
              </Table.Body>
          </Table>

          <Button className="full-list-link">View Full List</Button>

          </div>;
  }
}
