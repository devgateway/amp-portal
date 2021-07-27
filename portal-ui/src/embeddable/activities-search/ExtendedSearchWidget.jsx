import React from 'react';
import { Button, Dropdown, Form, Input, Pagination } from "semantic-ui-react";
import './ExtendedSearchWidget.scss';
import organisations from './json/organizations.json'
import sectors from './json/sectors.json'
import locations from './json/locations.json'
import TopList from '../top-lists/TopList';
import activityData from './json/activityResult.json';

const ExtendedSearchWidget = (props) => {

  const getOrganisations = () => {
    const elements = [];
    organisations.items.organizations.filter(o => {
      if (o.children) {
        const oTempChildren = o.children.filter(o2 => {
          const tempChildren2 = o2.children.filter(o3 => {
            return o3.listDefinitionIds.includes(1);
          })
          if (tempChildren2.length > 0) {
            o2.children = [...tempChildren2];
            return true
          }
          return false;
        })
        if (oTempChildren.length > 0) {
          o.children = [...oTempChildren];
          return true;
        }
        return false;
      } else {
        return false;
      }
    })
    organisations.items.organizations.forEach(o => {
      let level = 1;
      addToMap(o, elements, '', level);
    })
    return elements;
  }
  const getSectors = (scheme) => {
    return getElements(sectors.items[scheme]);

  }
  const getLocations = () => {
    return getElements(locations.items.locations);

  }
  const getElements = (originalArray) => {
    const elements = [];
    originalArray.forEach(s => {
      let level = 1;
      addToMap(s, elements, '', level);
    })
    return elements;
  }
  const addToMap = (object, arrayOfObjects, ancestor, level) => {
    arrayOfObjects.push({
      key: object.id,
      text: ancestor + object.name,
      value: object.id,
      level: level
    });
    if (object.children) {
      object.children.forEach(c => addToMap(c, arrayOfObjects, `${ancestor}  ${object.name} ->`, level + 1))
    }
  }
  const { labels } = props;
  const tableLabels = {};
  const fields = [];
  fields.push('project-title');
  fields.push("donor-agency")
  fields.push("primary-sector")
  fields.push('actual-commitments');
  fields.push('actual-disbursements');
  return <>
    <div className={"search-widget"}>
      <div className="list-header">
        <h3>{labels.title}</h3>
      </div>
      <Form>
        <Form.Field>
          <label>{labels.description}</label>
          <Input placeholder={labels.hint} type='text' />
        </Form.Field>
        <Form.Field>
          <label>Donor Agency</label>
          <Dropdown
            placeholder='Donor Agency'
            fluid
            multiple
            search
            selection
            options={getOrganisations()}
          />
        </Form.Field>
        <Form.Field>
          <label>Primary Sector</label>
          <Dropdown
            placeholder='Primary Sector'
            fluid
            multiple
            search
            selection
            options={getSectors('primary')}
          />
        </Form.Field>
        <Form.Field>
          <label>Secondary Sector</label>
          <Dropdown
            placeholder='Secondary'
            fluid
            multiple
            search
            selection
            options={getSectors('secondary')}
          />
        </Form.Field>
        <Form.Field>
          <label>Locations</label>
          <Dropdown
            placeholder='Locations'
            fluid
            multiple
            search
            selection
            options={getLocations()}
          />
        </Form.Field>
        <Button className="primary-button" type='link'>{labels.button}</Button>
      </Form>

    </div>
    <div>
      <div className="results-value">Activity result 1-10 of 64</div>
      <TopList data={activityData} labels={tableLabels} identity="activity-id" fields={fields} header isBigTable/>
      <Pagination defaultActivePage={5} totalPages={10} />
      {//TODO GALI TO ADD TOTALS
      }
    </div>
  </>;
}
export default ExtendedSearchWidget;
