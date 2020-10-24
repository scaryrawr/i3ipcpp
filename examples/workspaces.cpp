/**
 * This program dumps a tree of windows and workspaces to console
 */

#include <algorithm>
#include <iostream>

#include <i3ipc++/ipc.hpp>


/**
 * Reqursively dump containers of a tree
 * @param  c      a root container
 * @param  prefix an alignment
 */
void  dump_tree_container(const i3ipc::container_t&  c, std::string&  prefix) {
	std::cout << prefix << "ID: " << c.id << " (i3's; X11's - " << c.xwindow_id << ")" << std::endl;
	prefix.push_back('\t');
	std::cout << prefix << "name = \"" << c.name << "\"" << std::endl;
	std::cout << prefix << "type = \"" << c.type << "\"" << std::endl;
	std::cout << prefix << "class = \"" << c.window_properties.xclass << "\"" << std::endl;
	std::cout << prefix << "border = \"" << c.border_raw << "\"" << std::endl;
	std::cout << prefix << "current_border_width = " << c.current_border_width << std::endl;
	std::cout << prefix << "layout = \"" << c.layout_raw << "\"" << std::endl;
	std::cout << prefix << "percent = " << c.percent << std::endl;
	if (c.workspace.has_value()) {
		std::cout << prefix << "workspace = " << c.workspace.value() << std::endl;
	}
	if (c.sticky.has_value()) {
		std::cout << prefix << "sticky = " << c.sticky.value() << std::endl;
	}
	if (c.visible.has_value()) {
		std::cout << prefix << "visible = " << c.visible.value() << std::endl;
	}
	if (c.inhibit_idle.has_value()) {
		std::cout << prefix << "inhibit_idle = " << c.inhibit_idle.value() << std::endl;
	}
	if (c.fullscreen_mode.has_value()) {
		std::cout << prefix << "fullscreen_mode = " << static_cast<int>(c.fullscreen_mode.value()) << std::endl;
	}
	if (c.pid.has_value()) {
		std::cout << prefix << "pid = " << c.pid.value() << std::endl;
	}
	if (c.window.has_value()) {
		std::cout << prefix << "window = " << c.window.value() << std::endl;
	}
	if (c.app_id.has_value()) {
		std::cout << prefix << "app_id = " << c.app_id.value() << std::endl;
	}
	if (c.representation.has_value()) {
		std::cout << prefix << "representation = " << c.representation.value() << std::endl;
	}
	if (c.shell.has_value()) {
		std::cout << prefix << "shell = " << c.shell.value() << std::endl;
	}
	if (c.focus.has_value()) {
		std::cout << prefix << "focus = ";
		for (auto& focus_id : c.focus.value()) {
			std::cout << focus_id << ", ";
		}

		std::cout << std::endl;
	}
	if (c.marks.has_value()) {
		std::cout << prefix << "marks = ";
		for (auto& mark : c.marks.value()) {
			std::cout << mark << ", ";
		}

		std::cout << std::endl;
	}
	if (c.urgent) {
		std::cout << prefix << "urgent" << std::endl;
	}
	if (c.focused) {
		std::cout << prefix << "focused" << std::endl;
	}
	prefix.push_back('\t');
	for (auto&  n : c.nodes) {
		dump_tree_container(*n, prefix);
	}
	prefix.pop_back();
	prefix.pop_back();
}


int  main() {
	// First of all needs to create a connection
	i3ipc::connection  conn;

	// Then we dump workspaces
	for (auto&  w : conn.get_workspaces()) {
		std::cout << '#' << std::hex << w->num << std::dec
			<< "\n\tName: " << w->name
			<< "\n\tVisible: " << w->visible
			<< "\n\tFocused: " << w->focused
			<< "\n\tUrgent: " << w->urgent
			<< "\n\tRect: "
			<< "\n\t\tX: " << w->rect.x
			<< "\n\t\tY: " << w->rect.y
			<< "\n\t\tWidth: " << w->rect.width
			<< "\n\t\tHeight: " << w->rect.height
			<< "\n\tOutput: " << w->output
			<< std::endl;
	}

	// Then we dump the tree
	std::string  prefix_buf;
	dump_tree_container(*conn.get_tree(), prefix_buf);

	return 0;
}
