# Open Home Designer

This program allows creation and editing of a digital model of a house. This includes information about:
- Floors (levels)
- Walls
- Rooms
- Floor, wall and ceiling surfaces
- Electrical, plumbing, HVAC, telecommunications, etc (infrastructure)
- Landscaping

It is designed for houses that already exist, so its primary purpose is to document what is already there.

It is designed to store its data in a human-readable, version-controllable JSON file so that version control tools like Git can be used to keep track of changes over time.

The data captured will be renderable in 2D and 3D, and also exportable in tabular format, e.g. to support energy calculations. However this program itself will eventually include sophisticated energy calculations by allowing thermal properties to be captured (e.g. insulation status of walls, R-value on windows).

Other key features include:
- Capturing design alternatives (e.g. for an alteration, easily switch between current-state, Option 1 and Option 2), whether it's as small as different curtains, or as large as a whole new room
- Rendering the landscape around the house so you can see the view from the windows

Inspiration:
- Chief Architect Home Designer Suite
- Sweet Home 3D

## Name ideas

- OpenHome
- Home Modeller
- Homestead
- Homestead 3D
- Homestead Designer
- MyHome
- MyHome 3D

## Data

Positional data will be stored in integer millimetres. The origin is toward the top-left, with x increasing to the right and y increasing downwards. This is different from cartesian cooridinates, but in line with many 2D rendering tools.

### Walls

Walls are stored as a start and end position, and a thickness which includes the framing and cladding. The positions refer to the centreline of the wall.

#### Wall Sections

A wall can have sections along its length, which are specified by a starting and ending linear length along the wall (e.g. start: 0, end: 2135mm, meaning the first 2135mm from the start of the wall). This can be used when part of a wall has different properties from another part (possibly due to being part of a different room).