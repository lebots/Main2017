## Main2017
Main Robot code for Vex Starstruck

### Controls
| Mech.  | Desc.      | L/R   | Axis/Button    | Action | Notes |
| ------ | ---------- | ----- | -------------- | ------ | ----- |
| Drive  | Omni-direc |
| Arm    | Full Up    | **L** | Top Bumper     | Press  |
| Arm    | High Fence | **L** | Right on D-Pad | Press  | Also spreads arm out wide |
| Arm    | Low Fence  | **L** | Down on D-Pad  | Press  | Also spreads arm out wide |
| Arm    | Full Down  | **L** | Bottom Bumper  | Press  |
| Arm    | Climb Prep | **L** | Up on D-Pad    | Press  |
| Arm    | Climb      | **L** | Left on D-Pad  | Hold   | Also runs drive motors forward |
| Arm    | Lock       | _R_   | Up on D-Pad    | Hold   |
| Arm    | Unlock     | _R_   | Down on D-Pad  | Hold   |
| Hugger | Close      | _R_   | Top Bumper     | Hold   |
| Hugger | 90°        | _R_   | Bottom Bumper  | Press  |
| Hugger | 180°       | _R_   | Right on D-Pad | Press  |

### Secondary Controls
| Mech.  | Desc.      | L/R   | Axis/Button    | Action | Notes |
| ------ | ---------- | ----- | -------------- | ------ | ----- |
| Drive  | Omni-direc |
| Arm    | Climb      | **L** | Left on D-Pad  | Hold   | Also runs drive motors forward |
| Arm    | Lock       | _R_   | Up on D-Pad    | Hold   |
| Arm    | Unlock     | _R_   | Down on D-Pad  | Hold   |

### Motor ports
| Var Name | Port # |
| -------- | ------ |
| LHug     | 1      |
| LArm     | 2-4    |
| LDrive   | 5      |
| RArm     | 6-8    |
| RDrive   | 9      |
| armLock  | 10     |

### Sensor ports
| Var Name           | Type | Port # |
| ------------------ | ---- | ------ |
| armAngleSensor     | Pot  | 1 |
| hugAngleSensor     | Pot  | 2 |
| ratchetAngleSensor | Pot  | 3 |
| leftEncoderSensor  | Enc  | 1-2 |
| rightEncoderSensor | Enc  | 3-4 |

### X-Motor ports
| Var Name | Port # |
| -------- | ------ |
| LHug     | 1      |
| L1Arm    | 2      |
| FLDrive  | 3      |
| BLDrive  | 4      |
| L2Arm    | 5      |
| R1Arm    | 6      |
| R2Arm    | 7      |
| FRDrive  | 8      |
| BRDrive  | 9      |
| armLock  | 10     |

### X-Sensor ports
| Var Name           | Type | Port # |
| ------------------ | ---- | ------ |
| armAngleSensor     | Pot  | 1 |
| hugAngleSensor     | Pot  | 2 |
| ratchetAngleSensor | Pot  | 3 |
| FLEncoderSensor    | Enc  | 1-2 |
| BLEncoderSensor    | Enc  | 3-4 |
| FREncoderSensor    | Enc  | 5-6 |
| BREncoderSensor    | Enc  | 7-8 |
| auto3              | Jump | 10 |
| auto1              | Jump | 11 |
| auto2              | Jump | 12 |