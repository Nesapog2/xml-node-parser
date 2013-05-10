//
//  XMLNodeParser.h
//  NodeParser
//
//  Created by Robert Ryan on 5/9/13.
//  Copyright (c) 2013 Robert Ryan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ParserNode.h"

/**
 
 This is a subclass of the standard `NSXMLParser` class, which parsers the XML
 into a nested structure of `ParserNode` objects.
 
 **Example**
 
 Imagine a XML of the format:
 
    <Schools>
        <School>
            <ID>335823</ID>
            <Name>Fairfax High School</Name>
            <Students>
                <Student>
                    <ID>4195653</ID>
                    <Name>Will Turner</Name>
                </Student>
                <Student>
                    <ID>4195654</ID>
                    <Name>Bruce Paltrow</Name>
                </Student>
                <Student>
                    <ID>4195655</ID>
                    <Name>Santosh Gowswami</Name>
                </Student>
            </Students>
        </School>
    </Schools>

 You could parse this XML like so:
 
    XMLNodeParser *parser = [[XMLNodeParser alloc] initWithContentsOfURL:url];
    [parser parse];

    ParserNode *schools = parser.results;
    ParserNode *school = schools[0];
    NSLog(@"first school name = %@", school[@"Name"]);
    ParserNode *students = school[@"Students"];
    NSLog(@"there are %d students", students.count);
    NSLog(@"third student at that school = %@", students[2][@"Name"]);

 That generates the following output:
 
    2013-05-09 12:48:38.995 NodeParser[16366:c07] first school name = Fairfax High School
    2013-05-09 12:48:38.998 NodeParser[16366:c07] there are 3 students
    2013-05-09 12:48:38.999 NodeParser[16366:c07] third student at that school = Santosh Gowswami

 @warning This was written using ARC. If you are not using ARC, you may have to alter this code accordingly.
 
 Also note that the use of the "boxing" syntax (e.g. `schools[0]` or `student[@"Name"]` requires Xcode 4.5 or greater.
 
 @see ParserNode
 @see NSXMLParser
 */

@interface XMLNodeParser : NSXMLParser

/// @name Properties

/** The results represented as a ParserNode.
 *
 * @see `ParserNode`
 */

@property (nonatomic, strong) ParserNode *results;

- (void)setDelegate:(id<NSXMLParserDelegate>)delegate __attribute__ ((deprecated));

@end
