#import <Cocoa/Cocoa.h>

void setBadge(int count)
{
    [[NSApp dockTile] setBadgeLabel: [NSString stringWithFormat: @"%d", count]];
}

void clearBadge()
{
    [[NSApp dockTile] setBadgeLabel: @""];
}
