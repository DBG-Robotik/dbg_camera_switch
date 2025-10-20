from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # Vordere Kamera (usb_cam)
        Node(
            package="camera_ros",
            executable="camera_node",
            name="front_camera",
            parameters=[
                {'camera_name': 'front_camera',
                'video_device': '/dev/video0',
                'camera_info_url': '',  # Leer lassen, um libcamera zu nutzen
                'pixel_format': 'MJPEG',  # oder 'RGB8', je nach Kamera
                'io_method': 'mmap',  # Standard für libcamera
                }
            ],
            remappings=[
                ("image_raw", "front_camera/image_raw")  # Umbenennung des Topics
            ]
        ),
        # Hintere Kamera (usb_cam)
        #Node(
        #    package="usb_cam",
        #    executable="usb_cam_node_exe",
        #    name="back_camera",
        #    parameters=[
        #        {"video_device": "/dev/video_back"}
        #    ],
        #    remappings=[
        #        ("image_raw", "back_camera/image_raw")  # Umbenennung des Topics
        #    ]
        #),
        # Kamera-Switch-Knoten
        Node(
            package="dbg_camera_switch",
            executable="camera_switch_node",
            name="camera_switch_node"
        )
    ])