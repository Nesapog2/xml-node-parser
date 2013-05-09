//
//  ViewController.m
//  NodeParser
//
//  Created by Robert Ryan on 5/9/13.
//  Copyright (c) 2013 Robert Ryan. All rights reserved.
//

#import "ViewController.h"
#import "XMLNodeParser.h"

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    NSURL *url = [[NSBundle mainBundle] URLForResource:@"test" withExtension:@"xml"];
    
    XMLNodeParser *parser = [[XMLNodeParser alloc] initWithContentsOfURL:url];
    [parser parse];
    
    ParserNode *schools = parser.results;
    ParserNode *school = schools[0];
    NSLog(@"first school name = %@", school[@"Name"]);
    ParserNode *students = school[@"Students"];
    NSLog(@"there are %d students", students.count);
    NSLog(@"third student at that school = %@", students[2][@"Name"]);
}

@end
