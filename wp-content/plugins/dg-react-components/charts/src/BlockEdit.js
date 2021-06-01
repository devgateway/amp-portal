import {Component} from '@wordpress/element'
import {InspectorControls, useBlockProps} from '@wordpress/block-editor';
import {Panel, PanelBody, PanelRow, ResizableBox, SelectControl, TextControl, ToggleControl } from '@wordpress/components';
import {InnerBlocks} from '@wordpress/editor'; // or wp.editor
import {__} from '@wordpress/i18n';
import {Checkbox} from 'semantic-ui-react'




class BlockEdit extends Component {


    constructor(props) {
        super(props);
        this.colors = [
            {value: "nivo", label: 'nivo'},
            {value: "category10", label: 'category10'},
            {value: "accent", label: 'None'},
            {value: "dark2", label: 'dark2'},
            {value: "paired", label: 'paired'},
            {value: "pastel1", label: 'pastel1'},
            {value: "pastel2", label: 'pastel2'},
            {value: "set1", label: 'set1'},
            {value: "set2", label: 'set2'},
            {value: "set3", label: 'set3'}]
        this.dimensions = [
            {value: 'do', label: 'Donor Agency'},
            {value: "ro", label: 'Responsible Organization'},
            {value: "ba", label: 'Beneficiary Agency'},
            {value: "ia", label: 'Implementing Agency'},
            {value: "ea", label: 'Executing Agency'},
            {value: "re", label: 'Administrative Level 1'},
            {value: "ps", label: 'Primary Sector'},
            {value: "dg", label: 'Donor Group'}
        ]
      this.columns = [
        {value: 3, label: '3'},
        {value: 4, label: '4'},
        {value: 5, label: '5'}
      ]

    }

    componentDidUpdate(prevProps, prevState, snapshot) {
        const {
            setAttributes,
            attributes: {},
        } = this.props;

        if (prevProps.attributes) {
        }

    }

    componentDidMount() {
        const {
            setAttributes,
            isSelected,
            attributes: {
                height,
                type,
                source,
                bottom,
                left,
                scheme,
                colorBy
            }
        } = this.props;

    }


    render() {
        const {
            isSelected,
            toggleSelection, setAttributes, attributes: {
                height,
                width,
                type,
                groupMode,
                bottomLegend,
                leftLegend,
                scheme,
                colorBy,
                level1,
                level2,
                mode,
                dualMode,
            }
        } = this.props;

        const levels = [level1, level2];
        const source = levels.filter(l => l != 'none' && l != null).join('/')

        // 'data-legends-left': left = 'Left Legend',
        //         'data-legends-bottom': bottom = 'Bottom Legend',
        //
        const queryString = `data-height=${height}&data-chart-type=${type}&data-source=${source}&data-color-by=${colorBy}&data-color-scheme=${scheme}&data-scheme=${scheme}&data-group-mode=${groupMode}&data-legends-left=${leftLegend}&data-legends-bottom=${bottomLegend}&data-dualmode=${dualMode}&editing=true`
        const divStyles = {height: height + 'px', width: '100%'}

        return ([isSelected && (<InspectorControls>
                <Panel header={__("Chart Configuration")}>
                    <PanelBody>

                        <PanelRow>
                            <ToggleControl
                                label="Use Infographic"
                                checked={ dualMode }
                                onChange={ (dualMode) =>setAttributes({dualMode}) }
                            />
                        </PanelRow>
                        <PanelRow>

                            <SelectControl
                                label={__('Type:')}
                                value={[type]} // e.g: value = [ 'a', 'c' ]
                                onChange={(value) => {
                                    setAttributes({type: value})
                                }}
                                options={[{label: 'Bar', value: 'bar'},
                                  {label:'Top Chart',value: 'TopChart'},
                                  {label: 'Half Pie',value: 'halfPie'},
                                  {label: 'Donor Scorecard', value: 'donorScorecard'},
                                  {label: 'Diverging', value: 'diverging'}]}
                            />

                        </PanelRow>
                      <PanelRow>
                            <SelectControl
                                label={__('Group Mode')}
                                value={[groupMode]} // e.g: value = [ 'a', 'c' ]
                                onChange={(value) => {
                                    setAttributes({groupMode: value})
                                }}
                                options={[{label: 'Stacked', value: 'stacked'}, {
                                    label: 'Grouped', value: 'grouped'
                                }]}
                            />
                        </PanelRow>
                        <PanelRow>
                            <SelectControl
                                label={__('Datasource')}
                                value={[this.props.attributes.level1]} // e.g: value = [ 'a', 'c' ]
                                onChange={(value) => {
                                    setAttributes({level1: value})
                                }}
                                options={this.dimensions}
                            />
                        </PanelRow>

                        <PanelRow>
                            <SelectControl
                                label={__('Bar count')}
                                value={[this.props.attributes.level2]} // e.g: value = [ 'a', 'c' ]
                                onChange={(value) => {
                                    setAttributes({level2: value})
                                }}
                                options={this.columns}
                            />
                        </PanelRow>
                        <PanelRow>
                            <SelectControl
                                label={__('Color By')}
                                value={[colorBy]} // e.g: value = [ 'a', 'c' ]
                                onChange={(value) => {
                                    setAttributes({colorBy: value})
                                }}
                                options={[{label: 'Index', value: 'index'}, {label: 'Keys', value: 'keys'}]}
                            />
                        </PanelRow>
                        <PanelRow>
                            <SelectControl
                                label={__('Color Scheme')}
                                value={[scheme]} // e.g: value = [ 'a', 'c' ]
                                onChange={(value) => {
                                    setAttributes({scheme: value})
                                }}
                                options={this.colors}
                            />
                        </PanelRow>

                        <PanelRow>
                            <SelectControl
                                label={__('Left Legend')}
                                value={[scheme]} // e.g: value = [ 'a', 'c' ]
                                onChange={(value) => {
                                    setAttributes({scheme: value})
                                }}
                                options={this.colors}
                            />
                        </PanelRow>

                        <PanelRow>
                            <TextControl
                                label={__('Left Legend')}
                                value={leftLegend}
                                onChange={(leftLegend) => setAttributes({leftLegend})}
                            />
                        </PanelRow>
                        <PanelRow>
                            <TextControl
                                label={__('Chart title')}
                                value={bottomLegend}
                                onChange={(bottomLegend) => setAttributes({bottomLegend})}
                            />
                        </PanelRow>
                    </PanelBody>
                </Panel>
            </InspectorControls>),

                (<ResizableBox
                        size={{height}}
                        style={{"margin": "auto", width:"100%"}}
                        minHeight="50"
                        minWidth="50"
                        enable={{
                            top: false,
                            right: true,
                            bottom: true,
                            left: false,
                            topRight: false,
                            bottomRight: true,
                            bottomLeft: false,
                            topLeft: false,
                        }}
                        onResizeStop={(event, direction, elt, delta) => {
                            setAttributes({
                                height: parseInt(height + delta.height, 10),
                                width: parseInt(width + delta.width, 10),
                            });
                            toggleSelection(true);
                        }}
                        onResizeStart={() => {
                            toggleSelection(false);
                        }}
                    >
                        <div className="chart container" style={divStyles} >
                            <div>
                                {dualMode&&<Checkbox toggle defaultChecked={true}
                                           onChange={e => setAttributes({mode: (mode == 'chart' ? 'info' : 'chart')})}/>}
                            </div>

                            {mode == "chart" && <div>
                                <iframe scrolling={"no"} style={divStyles}
                                        src={process.env.EMBEDDABLE_URI + "/chart?" + queryString}/>
                            </div>}
                            {mode  == "info" && <div className={"inner block"}>
                                <InnerBlocks/>
                            </div>
                            }
                        </div>
                    </ResizableBox>
                )]
        );

    }
}


const Edit=(props)=>{

        const blockProps = useBlockProps( );

        return <div { ...blockProps }><BlockEdit {...props}/></div>;


}
export default Edit;