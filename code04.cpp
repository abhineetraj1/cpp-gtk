#include <gtkmm.h>
#include <fstream>
#include <iostream>

class TextEditor : public Gtk::Window {
public:
  TextEditor();
  virtual ~TextEditor();
protected:
  void on_new_file_click();
  void on_open_file_click();
  void on_save_file_click();
  void on_quit_click();
private:
  Gtk::Box m_vbox;
  Gtk::MenuBar m_menu_bar;
  Gtk::MenuItem m_file_menu_item;
  Gtk::Menu m_file_menu;
  Gtk::MenuItem m_new_file_item, m_open_file_item, m_save_file_item, m_quit_item;
  Gtk::ScrolledWindow m_text_area_scrolled_window;
  Gtk::TextView m_text_area;
  Glib::RefPtr<Gtk::TextBuffer> m_buffer;
  std::string m_current_file_path;
};

TextEditor::TextEditor() :
  m_vbox(Gtk::ORIENTATION_VERTICAL, 0),
  m_menu_bar(),
  m_file_menu_item("_File", true),
  m_file_menu(),
  m_new_file_item("_New File"),
  m_open_file_item("_Open File"),
  m_save_file_item("_Save File"),
  m_quit_item("_Quit"),
  m_text_area_scrolled_window(),
  m_text_area(),
  m_buffer(Gtk::TextBuffer::create())
{
  // Set up the text area
  m_text_area.set_buffer(m_buffer);
  m_text_area_scrolled_window.add(m_text_area);

  // Set up the menu bar
  m_file_menu_item.set_submenu(m_file_menu);
  m_file_menu.append(m_new_file_item);
  m_file_menu.append(m_open_file_item);
  m_file_menu.append(m_save_file_item);
  m_file_menu.append(m_quit_item);
  m_menu_bar.append(m_file_menu_item);

  // Set up the window
  add(m_vbox);
  m_vbox.pack_start(m_menu_bar, Gtk::PACK_SHRINK);
  m_vbox.pack_start(m_text_area_scrolled_window);

  // Connect signals
  m_new_file_item.signal_activate().connect(sigc::mem_fun(*this, &TextEditor::on_new_file_click));
  m_open_file_item.signal_activate().connect(sigc::mem_fun(*this, &TextEditor::on_open_file_click));
  m_save_file_item.signal_activate().connect(sigc::mem_fun(*this, &TextEditor::on_save_file_click));
  m_quit_item.signal_activate().connect(sigc::mem_fun(*this, &TextEditor::on_quit_click));

  // Show the window
  show_all_children();
}

TextEditor::~TextEditor() {}

void TextEditor::on_new_file_click() {
  m_buffer->set_text("");
  m_current_file_path.clear();
}

void TextEditor::on_open_file_click() {
  Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*this);
  dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  dialog.add_button("_Open", Gtk::RESPONSE_OK);
  int result = dialog.run();
  if (result == Gtk::RESPONSE_OK) {
    std::string file_path = dialog.get_filename();
    std::ifstream input_file(file_path);
    if (input_file.is_open()) {
      std::stringstream buffer;
      buffer << input_file.rdbuf();
      std::string text = buffer.str();
      m_buffer->set_text(text);
      m_current_file_path = file_path;
    } else {
      std::cerr << "Could not open file: " << file_path << std::endl;
    }
  }
}

void TextEditor::on_save_file_click() {
  if (m_current_file_path.empty()) {
    Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*this);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Save", Gtk::RESPONSE_OK);
    int result = dialog.run();
    if (result == Gtk::RESPONSE_OK) {
      m_current_file_path = dialog.get_filename();
    }
  }
  if (!m_current_file_path.empty()) {
    std::ofstream output_file(m_current_file_path);
    if (output_file.is_open()) {
      std::string text = m_buffer->get_text();
      output_file << text;
    } else {
      std::cerr << "Could not open file: " << m_current_file_path << std::endl;
    }
  }
}

void TextEditor::on_quit_click() {
  hide();
}

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
  TextEditor editor;
  return app->run(editor);
}
