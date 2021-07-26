import React, { Component } from 'react';
import { Button, Form, Input } from "semantic-ui-react";
import './SearchWidget.scss';
import { useLocation } from "react-router";

const SearchWidget = (props) => {
  const { labels, searchExtendedSlug } = props;
  return <div className={"search-widget"}>
    <div className="list-header">
      <h3>{labels.title}</h3>
    </div>
    <Form>
      <Form.Field>
        <label>{labels.description}</label>
        <Input icon='search' iconPosition='left' placeholder={labels.hint} type='text' />
      </Form.Field>
      <Button className="primary-button" type='link' as='a' href={`/#/en/${searchExtendedSlug}`}>{labels.button}</Button>
    </Form>
  </div>;
}
export default SearchWidget;
