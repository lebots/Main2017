## Main2017
Main Robot code for Vex Starstruck

### Controls
| Mech.  | Desc.      | L/R   | Axis/Button    | Action |
| ------ | ---------- | ----- | -------------- | ------ |
| Drive  | Left       | **L** | Y Axis         | Move   |
| Drive  | Right      | _R_   | Y Axis         | Move   |
| Arm    | Top        | **L** | Top Bumper     | Press  |
| Arm    | Bottom     | **L** | Bottom Bumper  | Press  |
| Arm    | Climb Prep | **L** | Up on D-Pad    | Press  |
| Arm    | Climb      | **L** | Left on D-Pad  | Hold   |
| Arm    | Tune Up    | **L** | Right on D-Pad | Hold   |
| Arm    | Tune Down  | **L** | Down on D-Pad  | Hold   |
| Arm    | Lock       | _R_   | Up on D-Pad    | Hold   |
| Hugger | Close      | _R_   | Top Bumper     | Hold   |
| Hugger | 90°        | _R_   | Bottom Bumper  | Press  |
| Hugger | 180°       | _R_   | Right on D-Pad | Press  |
| Hugger | Tune Open  | _R_   | Left on D-Pad  | Hold   |
| Hugger | Tune Close | _R_   | Down on D-Pad  | Hold   |


### Motor ports
| Var Name | Port # |
| -------- | ------ |
| LHug     | 1      |
| LArm     | 2-4    |
| LDrive   | 5      |
| RArm     | 6-8    |
| RDrive   | 9      |
| RHug     | 10     |

### Sensor ports
| Var Name           | Type | Port # |
| ------------------ | ---- | ------ |
| armAngleSensor     | Pot  | 1 |
| hugAngleSensor     | Pot  | 2 |
| leftEncoderSensor  | Enc  | 1-2 |
| rightEncoderSensor | Enc  | 3-4 |
