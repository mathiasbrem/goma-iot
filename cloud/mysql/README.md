# Goma IoT Database

## Overview

This database is designed to support a Goma IoT system. It organizes data related to buildings, locations, organizations, rooms, and sensors. The following sections provide an explanation of each table and their relationships.

## Tables

### 1. `building`

- **Description**: Stores information about buildings.
- **Columns**:
  - `building_id` (int, primary key, auto-increment): Unique identifier for each building.
  - `site_id` (int, foreign key): References the site to which the building belongs.
  - `building_name` (varchar(255)): Name of the building.
- **Indexes**:
  - `site_id`: Index for faster lookup by site ID.
- **Foreign Keys**:
  - `site_id` references `site(site_id)`.

### 2. `location`

- **Description**: Stores information about different geographical locations.
- **Columns**:
  - `location_id` (int, primary key, auto-increment): Unique identifier for each location.
  - `country` (varchar(50)): Country of the location.
  - `state` (varchar(50)): State of the location.
  - `city` (varchar(50)): City of the location.

### 3. `organization`

- **Description**: Stores information about organizations.
- **Columns**:
  - `organization_id` (int, primary key, auto-increment): Unique identifier for each organization.
  - `organization_name` (varchar(255)): Name of the organization.
  - `organization_type` (enum): Type of organization. Can be 'academic', 'industrial', or 'corporate'.

### 4. `room`

- **Description**: Stores information about rooms within buildings.
- **Columns**:
  - `room_id` (int, primary key, auto-increment): Unique identifier for each room.
  - `building_id` (int, foreign key): References the building to which the room belongs.
  - `room_number` (varchar(20)): Room number or identifier.
  - `latitude` (decimal(10,6)): Latitude coordinate of the room.
  - `longitude` (decimal(10,6)): Longitude coordinate of the room.
  - `capacity` (int): Capacity of the room.
  - `room_type` (enum): Type of room. Can be 'laboratory', 'classroom', 'office', or 'workshop'.
- **Indexes**:
  - `building_id`: Index for faster lookup by building ID.
- **Foreign Keys**:
  - `building_id` references `building(building_id)`.

### 5. `sensor`

- **Description**: Stores information about sensors deployed in rooms.
- **Columns**:
  - `sensor_id` (varchar(17), primary key): Unique identifier for each sensor.
  - `sensor_type` (varchar(50)): Type of sensor (e.g., 'energy', 'temperature').
  - `software_version` (varchar(50)): Software version of the sensor.
  - `hardware_version` (varchar(50)): Hardware version of the sensor.
  - `room_id` (int, foreign key): References the room in which the sensor is located.
- **Indexes**:
  - `room_id`: Index for faster lookup by room ID.
- **Foreign Keys**:
  - `room_id` references `room(room_id)`.

### 6. `site`

- **Description**: Stores information about sites where buildings are located.
- **Columns**:
  - `site_id` (int, primary key, auto-increment): Unique identifier for each site.
  - `location_id` (int, foreign key): References the location of the site.
  - `organization_id` (int, foreign key): References the organization managing the site.
  - `site_name` (varchar(255)): Name of the site.
- **Indexes**:
  - `location_id`: Index for faster lookup by location ID.
  - `organization_id`: Index for faster lookup by organization ID.
- **Foreign Keys**:
  - `location_id` references `location(location_id)`.
  - `organization_id` references `organization(organization_id)`.

## ER Diagram

The following diagram represents the relationships between the tables:

```plaintext
+------------------+         +--------------------+         +-----------------+
|     location     |         |     organization   |         |      site       |
|------------------|         |--------------------|         |-----------------|
| location_id (PK) |  <----  | organization_id (PK)|  <----  | site_id (PK)    |
| country          |         | organization_name  |         | location_id (FK)|
| state            |         | organization_type  |         | organization_id |
| city             |         |                    |         | site_name       |
+------------------+         +--------------------+         +-----------------+
                                                                 |
                                                                 |
                                                                 v
                                                 +---------------+-----------------+
                                                 |              building            |
                                                 |----------------------------------|
                                                 | building_id (PK)                 |
                                                 | site_id (FK)                     |
                                                 | building_name                    |
                                                 +----------------------------------+
                                                                 |
                                                                 |
                                                                 v
                                                 +---------------+-----------------+
                                                 |              room                |
                                                 |----------------------------------|
                                                 | room_id (PK)                     |
                                                 | building_id (FK)                 |
                                                 | room_number                      |
                                                 | latitude                         |
                                                 | longitude                        |
                                                 | capacity                         |
                                                 | room_type                        |
                                                 +----------------------------------+
                                                                 |
                                                                 |
                                                                 v
                                                 +---------------+-----------------+
                                                 |              sensor              |
                                                 |----------------------------------|
                                                 | sensor_id (PK)                   |
                                                 | sensor_type                      |
                                                 | software_version                 |
                                                 | hardware_version                 |
                                                 | room_id (FK)                     |
                                                 +----------------------------------+
```

# Sample Data

plaintext```

building:

| building_id | site_id | building_name |
|-------------|---------|---------------|
| 1           | 1       | Predio 3      |

location:

| location_id | country | state     | city      |
|-------------|---------|-----------|-----------|
| 1           | Brasil  | Sao Paulo | Sao Carlos|

organization:

| organization_id | organization_name | organization_type |
|-----------------|-------------------|-------------------|
| 1               | USP               | academic          |

room:

| room_id | building_id | room_number | latitude | longitude | capacity | room_type |
|---------|-------------|-------------|----------|-----------|----------|-----------|
| 1       | 1           | LAB1008     | 22.007000| -47.894900| 16       | laboratory|
| 2       | 1           | LAB1006     | 22.007000| -47.894900| 16       | laboratory|

sensor:

| sensor_id        | sensor_type | software_version | hardware_version | room_id |
|------------------|-------------|------------------|------------------|---------|
| 2C:3A:E8:0B:AC:18| energy      | 1.0              | 1.0              | 1       |
| EC:FA:BC:6C:48:46| temperature | 1.0              | 1.0              | 1       |
| EC:FA:BC:8F:1B:52| energy      | 1.0              | 1.0              | 1       |

site:

| site_id | location_id | organization_id | site_name |
|---------|-------------|-----------------|-----------|
| 1       | 1           | 1               | ICMC      |

```