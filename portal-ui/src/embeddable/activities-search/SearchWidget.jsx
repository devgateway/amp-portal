import React, { Component, useState } from 'react';
import { Button, Form, Input } from "semantic-ui-react";
import './SearchWidget.scss';
import { useLocation } from "react-router";

const SearchWidget = (props) => {
  const [keyword, setKeyword] = useState();
  const handleKeywordChange = (e, { value }) => {
    setKeyword(value);
  }
  const { labels, searchExtendedSlug, locale } = props;
  return <div className={"search-widget"}>
    <div className="list-header">
      <h3>{labels.title}</h3>
    </div>
    <Form>
      <Form.Field>
        <label>{labels.description}</label>
        <Input icon='search' iconPosition='left' placeholder={labels.hint} type='text' onChange={handleKeywordChange} />
      </Form.Field>
      <Button className="primary-button" type='link' as='a'
              href={`/#/${locale}/${searchExtendedSlug}?keyword=${keyword}`}>{labels.button}</Button>
    </Form>
  </div>;
}
export default SearchWidget;
